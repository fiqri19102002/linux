/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Avionic Design GmbH
 * Copyright (C) 2012-2013 NVIDIA CORPORATION.  All rights reserved.
 */

#ifndef HOST1X_DRM_H
#define HOST1X_DRM_H 1

#include <linux/host1x.h>
#include <linux/iova.h>
#include <linux/gpio/consumer.h>

#include <drm/drm_atomic.h>
#include <drm/drm_bridge.h>
#include <drm/drm_encoder.h>
#include <drm/drm_fixed.h>
#include <drm/drm_probe_helper.h>
#include <uapi/drm/tegra_drm.h>

#include "gem.h"
#include "hub.h"
#include "trace.h"

/* XXX move to include/uapi/drm/drm_fourcc.h? */
#define DRM_FORMAT_MOD_NVIDIA_SECTOR_LAYOUT BIT_ULL(22)

struct drm_fb_helper;
struct drm_fb_helper_surface_size;

struct edid;
struct reset_control;

struct tegra_drm {
	struct drm_device *drm;

	struct iommu_domain *domain;
	bool use_explicit_iommu;
	struct mutex mm_lock;
	struct drm_mm mm;

	struct {
		struct iova_domain domain;
		unsigned long shift;
		unsigned long limit;
	} carveout;

	struct mutex clients_lock;
	struct list_head clients;

	unsigned int hmask, vmask;
	unsigned int pitch_align;
	unsigned int num_crtcs;

	struct tegra_display_hub *hub;
};

static inline struct host1x *tegra_drm_to_host1x(struct tegra_drm *tegra)
{
	return dev_get_drvdata(tegra->drm->dev->parent);
}

struct tegra_drm_client;

struct tegra_drm_context {
	struct tegra_drm_client *client;
	struct host1x_channel *channel;

	/* Only used by legacy UAPI. */
	unsigned int id;

	/* Only used by new UAPI. */
	struct xarray mappings;
	struct host1x_memory_context *memory_context;
};

struct tegra_drm_client_ops {
	int (*open_channel)(struct tegra_drm_client *client,
			    struct tegra_drm_context *context);
	void (*close_channel)(struct tegra_drm_context *context);
	int (*is_addr_reg)(struct device *dev, u32 class, u32 offset);
	int (*is_valid_class)(u32 class);
	int (*submit)(struct tegra_drm_context *context,
		      struct drm_tegra_submit *args, struct drm_device *drm,
		      struct drm_file *file);
	int (*get_streamid_offset)(struct tegra_drm_client *client, u32 *offset);
	int (*can_use_memory_ctx)(struct tegra_drm_client *client, bool *supported);
};

int tegra_drm_submit(struct tegra_drm_context *context,
		     struct drm_tegra_submit *args, struct drm_device *drm,
		     struct drm_file *file);

static inline int
tegra_drm_get_streamid_offset_thi(struct tegra_drm_client *client, u32 *offset)
{
	*offset = 0x30;

	return 0;
}

struct tegra_drm_client {
	struct host1x_client base;
	struct list_head list;
	struct tegra_drm *drm;
	struct host1x_channel *shared_channel;

	/* Set by driver */
	unsigned int version;
	const struct tegra_drm_client_ops *ops;
};

static inline struct tegra_drm_client *
host1x_to_drm_client(struct host1x_client *client)
{
	return container_of(client, struct tegra_drm_client, base);
}

int tegra_drm_register_client(struct tegra_drm *tegra,
			      struct tegra_drm_client *client);
int tegra_drm_unregister_client(struct tegra_drm *tegra,
				struct tegra_drm_client *client);
int host1x_client_iommu_attach(struct host1x_client *client);
void host1x_client_iommu_detach(struct host1x_client *client);

void *tegra_drm_alloc(struct tegra_drm *tegra, size_t size, dma_addr_t *iova);
void tegra_drm_free(struct tegra_drm *tegra, size_t size, void *virt,
		    dma_addr_t iova);

struct cec_notifier;

struct tegra_output {
	struct device_node *of_node;
	struct device *dev;

	struct drm_bridge *bridge;
	struct drm_panel *panel;
	struct i2c_adapter *ddc;
	const struct drm_edid *drm_edid;
	struct cec_notifier *cec;
	unsigned int hpd_irq;
	struct gpio_desc *hpd_gpio;

	struct drm_encoder encoder;
	struct drm_connector connector;
};

static inline struct tegra_output *encoder_to_output(struct drm_encoder *e)
{
	return container_of(e, struct tegra_output, encoder);
}

static inline struct tegra_output *connector_to_output(struct drm_connector *c)
{
	return container_of(c, struct tegra_output, connector);
}

/* from output.c */
int tegra_output_probe(struct tegra_output *output);
void tegra_output_remove(struct tegra_output *output);
int tegra_output_init(struct drm_device *drm, struct tegra_output *output);
void tegra_output_exit(struct tegra_output *output);
void tegra_output_find_possible_crtcs(struct tegra_output *output,
				      struct drm_device *drm);
int tegra_output_suspend(struct tegra_output *output);
int tegra_output_resume(struct tegra_output *output);

int tegra_output_connector_get_modes(struct drm_connector *connector);
enum drm_connector_status
tegra_output_connector_detect(struct drm_connector *connector, bool force);
void tegra_output_connector_destroy(struct drm_connector *connector);

/* from dpaux.c */
struct drm_dp_aux *drm_dp_aux_find_by_of_node(struct device_node *np);
enum drm_connector_status drm_dp_aux_detect(struct drm_dp_aux *aux);
int drm_dp_aux_attach(struct drm_dp_aux *aux, struct tegra_output *output);
int drm_dp_aux_detach(struct drm_dp_aux *aux);
int drm_dp_aux_enable(struct drm_dp_aux *aux);
int drm_dp_aux_disable(struct drm_dp_aux *aux);

/* from fb.c */
struct tegra_bo *tegra_fb_get_plane(struct drm_framebuffer *framebuffer,
				    unsigned int index);
bool tegra_fb_is_bottom_up(struct drm_framebuffer *framebuffer);
int tegra_fb_get_tiling(struct drm_framebuffer *framebuffer,
			struct tegra_bo_tiling *tiling);
struct drm_framebuffer *tegra_fb_alloc(struct drm_device *drm,
				       const struct drm_format_info *info,
				       const struct drm_mode_fb_cmd2 *mode_cmd,
				       struct tegra_bo **planes,
				       unsigned int num_planes);
struct drm_framebuffer *tegra_fb_create(struct drm_device *drm,
					struct drm_file *file,
					const struct drm_format_info *info,
					const struct drm_mode_fb_cmd2 *cmd);

#ifdef CONFIG_DRM_FBDEV_EMULATION
int tegra_fbdev_driver_fbdev_probe(struct drm_fb_helper *helper,
				   struct drm_fb_helper_surface_size *sizes);
#define TEGRA_FBDEV_DRIVER_OPS \
	.fbdev_probe = tegra_fbdev_driver_fbdev_probe
#else
#define TEGRA_FBDEV_DRIVER_OPS \
	.fbdev_probe = NULL
#endif

extern struct platform_driver tegra_display_hub_driver;
extern struct platform_driver tegra_dc_driver;
extern struct platform_driver tegra_hdmi_driver;
extern struct platform_driver tegra_dsi_driver;
extern struct platform_driver tegra_dpaux_driver;
extern struct platform_driver tegra_sor_driver;
extern struct platform_driver tegra_gr2d_driver;
extern struct platform_driver tegra_gr3d_driver;
extern struct platform_driver tegra_vic_driver;
extern struct platform_driver tegra_nvdec_driver;

#endif /* HOST1X_DRM_H */
