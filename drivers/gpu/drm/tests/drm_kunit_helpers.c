// SPDX-License-Identifier: GPL-2.0

#include <drm/drm_atomic.h>
#include <drm/drm_atomic_helper.h>
#include <drm/drm_atomic_uapi.h>
#include <drm/drm_drv.h>
#include <drm/drm_edid.h>
#include <drm/drm_fourcc.h>
#include <drm/drm_kunit_helpers.h>
#include <drm/drm_managed.h>

#include <kunit/device.h>
#include <kunit/resource.h>

#include <linux/device.h>
#include <linux/export.h>
#include <linux/platform_device.h>

#define KUNIT_DEVICE_NAME	"drm-kunit-mock-device"

static const struct drm_mode_config_funcs drm_mode_config_funcs = {
	.atomic_check	= drm_atomic_helper_check,
	.atomic_commit	= drm_atomic_helper_commit,
};

/**
 * drm_kunit_helper_alloc_device - Allocate a mock device for a KUnit test
 * @test: The test context object
 *
 * This allocates a fake struct &device to create a mock for a KUnit
 * test. The device will also be bound to a fake driver. It will thus be
 * able to leverage the usual infrastructure and most notably the
 * device-managed resources just like a "real" device.
 *
 * Resources will be cleaned up automatically, but the removal can be
 * forced using @drm_kunit_helper_free_device.
 *
 * Returns:
 * A pointer to the new device, or an ERR_PTR() otherwise.
 */
struct device *drm_kunit_helper_alloc_device(struct kunit *test)
{
	return kunit_device_register(test, KUNIT_DEVICE_NAME);
}
EXPORT_SYMBOL_GPL(drm_kunit_helper_alloc_device);

/**
 * drm_kunit_helper_free_device - Frees a mock device
 * @test: The test context object
 * @dev: The device to free
 *
 * Frees a device allocated with drm_kunit_helper_alloc_device().
 */
void drm_kunit_helper_free_device(struct kunit *test, struct device *dev)
{
	kunit_device_unregister(test, dev);
}
EXPORT_SYMBOL_GPL(drm_kunit_helper_free_device);

struct drm_device *
__drm_kunit_helper_alloc_drm_device_with_driver(struct kunit *test,
						struct device *dev,
						size_t size, size_t offset,
						const struct drm_driver *driver)
{
	struct drm_device *drm;
	void *container;
	int ret;

	container = __devm_drm_dev_alloc(dev, driver, size, offset);
	if (IS_ERR(container))
		return ERR_CAST(container);

	drm = container + offset;
	drm->mode_config.funcs = &drm_mode_config_funcs;

	ret = drmm_mode_config_init(drm);
	if (ret)
		return ERR_PTR(ret);

	return drm;
}
EXPORT_SYMBOL_GPL(__drm_kunit_helper_alloc_drm_device_with_driver);

static void kunit_action_drm_atomic_state_put(void *ptr)
{
	struct drm_atomic_state *state = ptr;

	drm_atomic_state_put(state);
}

/**
 * drm_kunit_helper_atomic_state_alloc - Allocates an atomic state
 * @test: The test context object
 * @drm: The device to alloc the state for
 * @ctx: Locking context for that atomic update
 *
 * Allocates a empty atomic state.
 *
 * The state is tied to the kunit test context, so we must not call
 * drm_atomic_state_put() on it, it will be done so automatically.
 *
 * Returns:
 * An ERR_PTR on error, a pointer to the newly allocated state otherwise
 */
struct drm_atomic_state *
drm_kunit_helper_atomic_state_alloc(struct kunit *test,
				    struct drm_device *drm,
				    struct drm_modeset_acquire_ctx *ctx)
{
	struct drm_atomic_state *state;
	int ret;

	state = drm_atomic_state_alloc(drm);
	if (!state)
		return ERR_PTR(-ENOMEM);

	ret = kunit_add_action_or_reset(test,
					kunit_action_drm_atomic_state_put,
					state);
	if (ret)
		return ERR_PTR(ret);

	state->acquire_ctx = ctx;

	return state;
}
EXPORT_SYMBOL_GPL(drm_kunit_helper_atomic_state_alloc);

static const uint32_t default_plane_formats[] = {
	DRM_FORMAT_XRGB8888,
};

static const uint64_t default_plane_modifiers[] = {
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
};

static const struct drm_plane_helper_funcs default_plane_helper_funcs = {
};

static const struct drm_plane_funcs default_plane_funcs = {
	.atomic_destroy_state	= drm_atomic_helper_plane_destroy_state,
	.atomic_duplicate_state	= drm_atomic_helper_plane_duplicate_state,
	.reset			= drm_atomic_helper_plane_reset,
};

/**
 * drm_kunit_helper_create_primary_plane - Creates a mock primary plane for a KUnit test
 * @test: The test context object
 * @drm: The device to alloc the plane for
 * @funcs: Callbacks for the new plane. Optional.
 * @helper_funcs: Helpers callbacks for the new plane. Optional.
 * @formats: array of supported formats (DRM_FORMAT\_\*). Optional.
 * @num_formats: number of elements in @formats
 * @modifiers: array of struct drm_format modifiers terminated by
 *             DRM_FORMAT_MOD_INVALID. Optional.
 *
 * This allocates and initializes a mock struct &drm_plane meant to be
 * part of a mock device for a KUnit test.
 *
 * Resources will be cleaned up automatically.
 *
 * @funcs will default to the default helpers implementations.
 * @helper_funcs will default to an empty implementation. @formats will
 * default to XRGB8888 only. @modifiers will default to a linear
 * modifier only.
 *
 * Returns:
 * A pointer to the new plane, or an ERR_PTR() otherwise.
 */
struct drm_plane *
drm_kunit_helper_create_primary_plane(struct kunit *test,
				      struct drm_device *drm,
				      const struct drm_plane_funcs *funcs,
				      const struct drm_plane_helper_funcs *helper_funcs,
				      const uint32_t *formats,
				      unsigned int num_formats,
				      const uint64_t *modifiers)
{
	struct drm_plane *plane;

	if (!funcs)
		funcs = &default_plane_funcs;

	if (!helper_funcs)
		helper_funcs = &default_plane_helper_funcs;

	if (!formats || !num_formats) {
		formats = default_plane_formats;
		num_formats = ARRAY_SIZE(default_plane_formats);
	}

	if (!modifiers)
		modifiers = default_plane_modifiers;

	plane = __drmm_universal_plane_alloc(drm,
					     sizeof(struct drm_plane), 0,
					     0,
					     funcs,
					     formats,
					     num_formats,
					     default_plane_modifiers,
					     DRM_PLANE_TYPE_PRIMARY,
					     NULL);
	KUNIT_ASSERT_NOT_ERR_OR_NULL(test, plane);

	drm_plane_helper_add(plane, helper_funcs);

	return plane;
}
EXPORT_SYMBOL_GPL(drm_kunit_helper_create_primary_plane);

static const struct drm_crtc_helper_funcs default_crtc_helper_funcs = {
};

static const struct drm_crtc_funcs default_crtc_funcs = {
	.atomic_destroy_state   = drm_atomic_helper_crtc_destroy_state,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.reset                  = drm_atomic_helper_crtc_reset,
};

/**
 * drm_kunit_helper_create_crtc - Creates a mock CRTC for a KUnit test
 * @test: The test context object
 * @drm: The device to alloc the plane for
 * @primary: Primary plane for CRTC
 * @cursor: Cursor plane for CRTC. Optional.
 * @funcs: Callbacks for the new plane. Optional.
 * @helper_funcs: Helpers callbacks for the new plane. Optional.
 *
 * This allocates and initializes a mock struct &drm_crtc meant to be
 * part of a mock device for a KUnit test.
 *
 * Resources will be cleaned up automatically.
 *
 * @funcs will default to the default helpers implementations.
 * @helper_funcs will default to an empty implementation.
 *
 * Returns:
 * A pointer to the new CRTC, or an ERR_PTR() otherwise.
 */
struct drm_crtc *
drm_kunit_helper_create_crtc(struct kunit *test,
			     struct drm_device *drm,
			     struct drm_plane *primary,
			     struct drm_plane *cursor,
			     const struct drm_crtc_funcs *funcs,
			     const struct drm_crtc_helper_funcs *helper_funcs)
{
	struct drm_crtc *crtc;
	int ret;

	if (!funcs)
		funcs = &default_crtc_funcs;

	if (!helper_funcs)
		helper_funcs = &default_crtc_helper_funcs;

	crtc = drmm_kzalloc(drm, sizeof(*crtc), GFP_KERNEL);
	KUNIT_ASSERT_NOT_NULL(test, crtc);

	ret = drmm_crtc_init_with_planes(drm, crtc,
					 primary,
					 cursor,
					 funcs,
					 NULL);
	KUNIT_ASSERT_EQ(test, ret, 0);

	drm_crtc_helper_add(crtc, helper_funcs);

	return crtc;
}
EXPORT_SYMBOL_GPL(drm_kunit_helper_create_crtc);

/**
 * drm_kunit_helper_enable_crtc_connector - Enables a CRTC -> Connector output
 * @test: The test context object
 * @drm: The device to alloc the plane for
 * @crtc: The CRTC to enable
 * @connector: The Connector to enable
 * @mode: The display mode to configure the CRTC with
 * @ctx: Locking context
 *
 * This function creates an atomic update to enable the route from @crtc
 * to @connector, with the given @mode.
 *
 * Returns:
 *
 * A pointer to the new CRTC, or an ERR_PTR() otherwise. If the error
 * returned is EDEADLK, the entire atomic sequence must be restarted.
 */
int drm_kunit_helper_enable_crtc_connector(struct kunit *test,
					   struct drm_device *drm,
					   struct drm_crtc *crtc,
					   struct drm_connector *connector,
					   const struct drm_display_mode *mode,
					   struct drm_modeset_acquire_ctx *ctx)
{
	struct drm_atomic_state *state;
	struct drm_connector_state *conn_state;
	struct drm_crtc_state *crtc_state;
	int ret;

	state = drm_kunit_helper_atomic_state_alloc(test, drm, ctx);
	if (IS_ERR(state))
		return PTR_ERR(state);

	conn_state = drm_atomic_get_connector_state(state, connector);
	if (IS_ERR(conn_state))
		return PTR_ERR(conn_state);

	ret = drm_atomic_set_crtc_for_connector(conn_state, crtc);
	if (ret)
		return ret;

	crtc_state = drm_atomic_get_crtc_state(state, crtc);
	if (IS_ERR(crtc_state))
		return PTR_ERR(crtc_state);

	ret = drm_atomic_set_mode_for_crtc(crtc_state, mode);
	if (ret)
		return ret;

	crtc_state->enable = true;
	crtc_state->active = true;

	ret = drm_atomic_commit(state);
	if (ret)
		return ret;

	return 0;
}
EXPORT_SYMBOL_GPL(drm_kunit_helper_enable_crtc_connector);

static void kunit_action_drm_mode_destroy(void *ptr)
{
	struct drm_display_mode *mode = ptr;

	drm_mode_destroy(NULL, mode);
}

/**
 * drm_kunit_add_mode_destroy_action() - Add a drm_destroy_mode kunit action
 * @test: The test context object
 * @mode: The drm_display_mode to destroy eventually
 *
 * Registers a kunit action that will destroy the drm_display_mode at
 * the end of the test.
 *
 * If an error occurs, the drm_display_mode will be destroyed.
 *
 * Returns:
 * 0 on success, an error code otherwise.
 */
int drm_kunit_add_mode_destroy_action(struct kunit *test,
				      struct drm_display_mode *mode)
{
	return kunit_add_action_or_reset(test,
					 kunit_action_drm_mode_destroy,
					 mode);
}
EXPORT_SYMBOL_GPL(drm_kunit_add_mode_destroy_action);

/**
 * drm_kunit_display_mode_from_cea_vic() - return a mode for CEA VIC for a KUnit test
 * @test: The test context object
 * @dev: DRM device
 * @video_code: CEA VIC of the mode
 *
 * Creates a new mode matching the specified CEA VIC for a KUnit test.
 *
 * Resources will be cleaned up automatically.
 *
 * Returns: A new drm_display_mode on success or NULL on failure
 */
struct drm_display_mode *
drm_kunit_display_mode_from_cea_vic(struct kunit *test, struct drm_device *dev,
				    u8 video_code)
{
	struct drm_display_mode *mode;
	int ret;

	mode = drm_display_mode_from_cea_vic(dev, video_code);
	if (!mode)
		return NULL;

	ret = kunit_add_action_or_reset(test,
					kunit_action_drm_mode_destroy,
					mode);
	if (ret)
		return NULL;

	return mode;
}
EXPORT_SYMBOL_GPL(drm_kunit_display_mode_from_cea_vic);

MODULE_AUTHOR("Maxime Ripard <maxime@cerno.tech>");
MODULE_DESCRIPTION("KUnit test suite helper functions");
MODULE_LICENSE("GPL");
