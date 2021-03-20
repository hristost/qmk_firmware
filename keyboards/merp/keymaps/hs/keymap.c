#include QMK_KEYBOARD_H
#include "tlc59711.h"
#include <print.h>

#define A(x) LALT(x)
#define WW(x) LALT(LSFT(x))

// Momentary toggle to QWERTY with Ctrl + Alt + Shift (`Meh` modifier in skhd)
#define MEH_QWRT LM(_QWERTY, MOD_LCTL | MOD_LALT | MOD_LSFT)

extern keymap_config_t keymap_config;

enum preonic_layers {
  _DVORAK,
  _QWERTY,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  DVORAK = SAFE_RANGE,
  QWERTY,
  COLEMAK,
  LOWER,
  RAISE,
  BACKLIT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,  \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  \
  BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  LOWER,   RAISE,   KC_SPC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT   \
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,  \
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_SLSH, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
  BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Dvorak
 * ,-----------------------------------------.   ,-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   |   F  |   G  |   C  |   R  |   L  |   /  |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   |   D  |   H  |   T  |   N  |   S  |   =  |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   |   B  |   M  |   W  |   V  |   Z  | Shift|
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * | Fn   | Ctrl | Alt  | GUI  | Esc  | Tab  |   | Enter|      |   \  | Down |  Up  |Raise |
 * `-----------------------------------------'   `-----------------------------------------'
 *                               Ctrl   Lower      Raise
 */
[_DVORAK] = LAYOUT( \
  KC_GRV,        KC_1,    KC_2,    KC_3,    KC_4,          KC_5,               KC_6,                 KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,        KC_QUOT, KC_COMM, KC_DOT,  KC_P,          KC_Y,               KC_F,                 KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, \
  CTL_T(KC_ESC), KC_A,    KC_O,    KC_E,    KC_U,          KC_I,               KC_D,                 KC_H,    KC_T,    KC_N,    KC_S,    KC_EQL,  \
  KC_LSFT,       KC_SCLN, KC_Q,    KC_J,    KC_K,          KC_X,               KC_B,                 KC_M,    KC_W,    KC_V,    KC_Z,    KC_MINS, \
  KC_F19,        KC_LCTL, KC_LALT, KC_LGUI, CTL_T(KC_ESC), OSL(_LOWER),        LT(_RAISE, KC_ENTER), KC_SPC,  KC_NUHS, KC_DOWN, KC_RGUI, MEH_QWRT \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   &  |   \  |   (  |   )  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   _  |   =  |   [  |   ]  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   -  |   +  |   {  |   }  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT( \
  DVORAK,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
  QWERTY,  KC_AMPR, KC_BSLS, KC_LPRN, KC_RPRN, KC_CIRC, _______, _______, _______, _______, _______, _______, \
  BACKLIT, KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, KC_F6,   _______, _______, _______, _______, _______, _______, \
  _______, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, KC_F12,  _______, _______, _______, _______, _______, _______, \
  RESET,   OUT_USB, OUT_BT, OUT_AUTO, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Play | Vol- | Vol+ |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Left | Down |  Up  | Right|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_VOLD, KC_VOLU, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______, \
  RESET,   _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,  \
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  _______, _______, \
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tlc59711_process_matrix(keycode, record);
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
        case DVORAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DVORAK);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
                tlc59711_toggle_enabled();
#ifdef BACKLIGHT_ENABLE
                backlight_step();
#endif
                PORTE &= ~(1<<6);
            } else {
                unregister_code(KC_RSFT);
                PORTE |= (1<<6);
            }
            return false;
            break;
    }
    return true;
};
