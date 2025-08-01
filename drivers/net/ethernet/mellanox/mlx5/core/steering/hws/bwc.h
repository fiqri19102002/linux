/* SPDX-License-Identifier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2024 NVIDIA Corporation & Affiliates */

#ifndef HWS_BWC_H_
#define HWS_BWC_H_

#define MLX5HWS_BWC_MATCHER_INIT_SIZE_LOG 1
#define MLX5HWS_BWC_MATCHER_SIZE_LOG_STEP 1
#define MLX5HWS_BWC_MATCHER_REHASH_PERCENT_TH 70
#define MLX5HWS_BWC_MATCHER_REHASH_BURST_TH 32

/* Max number of AT attach operations for the same matcher.
 * When the limit is reached, a larger buffer is allocated for the ATs.
 */
#define MLX5HWS_BWC_MATCHER_ATTACH_AT_NUM 8

#define MLX5HWS_BWC_MAX_ACTS 16

#define MLX5HWS_BWC_POLLING_TIMEOUT 60

struct mlx5hws_bwc_matcher_complex_data;

struct mlx5hws_bwc_matcher_size {
	u8 size_log;
	atomic_t num_of_rules;
	atomic_t rehash_required;
};

struct mlx5hws_bwc_matcher {
	struct mlx5hws_matcher *matcher;
	struct mlx5hws_match_template *mt;
	struct mlx5hws_action_template **at;
	struct mlx5hws_bwc_matcher_complex_data *complex;
	struct mlx5hws_bwc_matcher *complex_first_bwc_matcher;
	u8 num_of_at;
	u8 size_of_at_array;
	u32 priority;
	struct mlx5hws_bwc_matcher_size rx_size;
	struct mlx5hws_bwc_matcher_size tx_size;
	struct list_head *rules;
};

struct mlx5hws_bwc_rule {
	struct mlx5hws_bwc_matcher *bwc_matcher;
	struct mlx5hws_rule *rule;
	struct mlx5hws_bwc_rule *isolated_bwc_rule;
	struct mlx5hws_bwc_complex_rule_hash_node *complex_hash_node;
	u32 flow_source;
	u16 bwc_queue_idx;
	bool skip_rx;
	bool skip_tx;
	struct list_head list_node;
};

int
mlx5hws_bwc_matcher_create_simple(struct mlx5hws_bwc_matcher *bwc_matcher,
				  struct mlx5hws_table *table,
				  u32 priority,
				  u8 match_criteria_enable,
				  struct mlx5hws_match_parameters *mask,
				  enum mlx5hws_action_type action_types[]);

int mlx5hws_bwc_matcher_destroy_simple(struct mlx5hws_bwc_matcher *bwc_matcher);

struct mlx5hws_bwc_rule *mlx5hws_bwc_rule_alloc(struct mlx5hws_bwc_matcher *bwc_matcher);

void mlx5hws_bwc_rule_free(struct mlx5hws_bwc_rule *bwc_rule);

int mlx5hws_bwc_rule_create_simple(struct mlx5hws_bwc_rule *bwc_rule,
				   u32 *match_param,
				   struct mlx5hws_rule_action rule_actions[],
				   u32 flow_source,
				   u16 bwc_queue_idx);

int mlx5hws_bwc_rule_destroy_simple(struct mlx5hws_bwc_rule *bwc_rule);

void mlx5hws_bwc_rule_fill_attr(struct mlx5hws_bwc_matcher *bwc_matcher,
				u16 bwc_queue_idx,
				u32 flow_source,
				struct mlx5hws_rule_attr *rule_attr);

int mlx5hws_bwc_queue_poll(struct mlx5hws_context *ctx,
			   u16 queue_id,
			   u32 *pending_rules,
			   bool drain);

static inline u16 mlx5hws_bwc_queues(struct mlx5hws_context *ctx)
{
	/* Besides the control queue, half of the queues are
	 * regular HWS queues, and the other half are BWC queues.
	 */
	if (mlx5hws_context_bwc_supported(ctx))
		return (ctx->queues - 1) / 2;
	return 0;
}

static inline u16 mlx5hws_bwc_get_queue_id(struct mlx5hws_context *ctx, u16 idx)
{
	return idx + mlx5hws_bwc_queues(ctx);
}

#endif /* HWS_BWC_H_ */
