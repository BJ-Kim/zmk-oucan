#include <zephyr/kernel.h>

#include <zmk/event_manager.h>
#include <zmk/events/ble_active_profile_changed.h>
#include <zmk/keymap.h>

// Keep these values in sync with the layer/profile defines in toucan.keymap.
#define WINDOWS_BASE_LAYER  1
#define WINDOWS_BLE_PROFILE 4

BUILD_ASSERT(WINDOWS_BASE_LAYER < ZMK_KEYMAP_LAYERS_LEN,
             "Windows base layer must exist in the keymap");

static int os_profile_listener(const zmk_event_t *eh) {
    const struct zmk_ble_active_profile_changed *event =
        as_zmk_ble_active_profile_changed(eh);

    if (event == NULL) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    if (event->index == WINDOWS_BLE_PROFILE) {
        zmk_keymap_layer_activate(WINDOWS_BASE_LAYER);
    } else {
        zmk_keymap_layer_deactivate(WINDOWS_BASE_LAYER);
    }

    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(toucan_os_profile, os_profile_listener);
ZMK_SUBSCRIPTION(toucan_os_profile, zmk_ble_active_profile_changed);
