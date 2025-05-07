//dynamic keymap definition
#include <stdint.h>
#include <zmk/keys.h>  //ZMK Keycode Definitions

#define NUM_DYNAMIC_KEYS 6    
                            //However many keys are in the matrix
uint32_t dynamic_keymap[NUM_DYNAMIC_KEYS] = {
    HID_USAGE_KEY_A, HID_USAGE_KEY_B,
    HID_USAGE_KEY_C, HID_USAGE_KEY_D,
    HID_USAGE_KEY_E, HID_USAGE_KEY_F
};

//dynmaic keycode behavior
#include <zmk/behavior.h>
#include <zmk/keycode.h>
#include <zmk/behavior_queue.h>

static int dynamic_key_press(struct zmk_behavior_binding *binding,
                             struct zmk_behavior_binding_event event) {
    uint8_t index = binding->param1;
    if (index >= NUM_DYNAMIC_KEYS) return -EINVAL;
    uint32_t keycode = dynamic_keymap[index];
    return zmk_behavior_queue_keycode_event(keycode, true, event);
}

static int dynamic_key_release(struct zmk_behavior_binding *binding,
                               struct zmk_behavior_binding_event event) {
    uint8_t index = binding->param1;
    if (index >= NUM_DYNAMIC_KEYS) return -EINVAL;
    uint32_t keycode = dynamic_keymap[index];
    return zmk_behavior_queue_keycode_event(keycode, false, event);
}

const struct behavior_driver_api dynamic_key_driver = {
    .binding_pressed = dynamic_key_press,
    .binding_released = dynamic_key_release,
};
