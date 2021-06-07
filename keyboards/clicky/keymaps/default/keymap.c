#include QMK_KEYBOARD_H
#include "clicky.h"
#include "action_layer.h"



// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum preonic_layers {
    _QWERTY,
    _DVORAK,
    _LOWER,
    _RAISE,
};

enum preonic_keycodes {
    SPOTLIGHT = SAFE_RANGE
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define ENTER LT(_RAISE, KC_ENTER)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


    /* Dvorak
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |  /   |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |   =  |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |   -  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | fn   | Ctrl | Alt  | GUI  | Alt  | Raise/Enter |      |   \  |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_DVORAK] = {
        {KC_GRV,        KC_1,    KC_2,    KC_3,    KC_4,     KC_5,    KC_6,  KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
        {KC_TAB,        KC_QUOT, KC_COMM, KC_DOT,  KC_P,     KC_Y,    KC_F,  KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH},
        {CTL_T(KC_ESC), KC_A,    KC_O,    KC_E,    KC_U,     KC_I,    KC_D,  KC_H,    KC_T,    KC_N,    KC_S,    KC_EQL},
        {KC_LSFT,       KC_SCLN, KC_Q,    KC_J,    KC_K,     KC_X,    KC_B,  KC_M,    KC_W,    KC_V,    KC_Z,    KC_MINS},
        {KC_F19,        KC_LCTL, KC_LALT, KC_LGUI, KC_LALT,  _______, ENTER, KC_SPC,  KC_NUHS, KC_DOWN, KC_RGUI, SPOTLIGHT}
    },

    /* Lower
     * ,-----------------------------------------------------------------------------------.
     * |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |  (   |   )  |      |      | Play | Vol- | Vol+ |      |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |      |      |  [   |   }  |      |      | Left | Down |  Up  | Right|      |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |      |  {   |   }  |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | RST  |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_RAISE] = {
        {KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11},
        {_______, KC_AMPR, KC_BSLS, KC_LPRN, KC_RPRN, KC_CIRC,  _______, KC_MPLY, KC_VOLD, KC_VOLU, _______, _______},
        {_______, KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, _______,  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______},
        {_______, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______,  _______, KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______},
        {RESET,   OUT_USB, OUT_BT, OUT_AUTO, _______, _______,  _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
    }


};


void persistant_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPOTLIGHT:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LGUI));
                SEND_STRING(SS_DOWN(X_SPACE));
            } else {
                SEND_STRING(SS_UP(X_LGUI));
                SEND_STRING(SS_UP(X_SPACE));
            }
            return false;
            break;
    }
    return true;
};

void matrix_init_user(void) {
}


void matrix_scan_user(void) {
}
