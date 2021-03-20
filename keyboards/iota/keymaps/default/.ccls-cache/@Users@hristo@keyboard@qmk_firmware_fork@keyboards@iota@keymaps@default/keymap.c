#include "iota.h"
#include "action_layer.h"



// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum preonic_layers {
  _QWERTY,
  //_SNEZHI,
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  //SNEZHI,
  DVORAK,
  LOWER,
  RAISE,
  SPOTLIGHT,
  LANGLANG
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  /   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc/C|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   "  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | Cmd  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_SLSH},
  {CTL_T(KC_ESC),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT, KC_RSHIFT },
  {KC_LCTL, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Minecraft
 * ,-----------------------------------------------------------------------------------.
 * | F1   |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | F2   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  /   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | F3   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | V+   |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  | V-   |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ^    | ^esc | Enter| Cmd  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
    /*
[_SNEZHI] = {
  {KC_F1,   KC_1,          KC_2,     KC_3,    KC_4,  KC_5,   KC_6,   KC_7,  KC_8,    KC_9,    KC_0,        KC_BSPC},
  {KC_F2,   KC_Q,          KC_W,     KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,        KC_SLSH},
  {KC_F3,   KC_A,          KC_S,     KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC__VOLUP,   KC_ENT},
  {KC_LSFT, KC_Z,          KC_X,     KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC__VOLDOWN, KC_RSHIFT },
  {KC_LCTL, CTL_T(KC_ESC), KC_ENTER, KC_LGUI, LOWER, KC_SPC, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,       KC_RGHT}
},
*/


/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |  /   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Shift | Raise/Enter |      | GUI  | Down |  Up  | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = {
  {KC_GRV,        KC_1,    KC_2,    KC_3,    KC_4,  KC_5,   KC_6,   KC_7,  KC_8,    KC_9,    KC_0,  KC_BSPC},
  {KC_TAB,        KC_QUOT, KC_COMM, KC_DOT,  KC_P,  KC_Y,   KC_F,   KC_G,  KC_C,    KC_R,    KC_L,  KC_SLSH},
  {CTL_T(KC_ESC), KC_A,    KC_O,    KC_E,    KC_U,  KC_I,   KC_D,   KC_H,  KC_T,    KC_N,    KC_S,  KC_ENT},
  {KC_LSFT,       KC_SCLN, KC_Q,    KC_J,    KC_K,  KC_X,   KC_B,   KC_M,  KC_W,    KC_V,    KC_Z,  KC_RSHIFT},
  {LANGLANG, SPOTLIGHT, KC_LALT, KC_LGUI, SFT_T(KC_BSPC), CTL_T(KC_ESC),  LT(_RAISE, KC_ENTER), KC_SPC, KC_RGUI, KC_DOWN, KC_UP, _______}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   &  |   \  |   (  |   )  |   %  |   ^  |   _  |   =  |   [  |   ]  | Del  |
 * |   `  |   &  |   \  |   (  |   )  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |   _  |   =  |   [  |   ]  |      |      | Left | Down |  Up  | Right|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   -  |   +  |   {  |   }  |      |      |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {RESET,   KC_SLCK, _______,  DVORAK,  QWERTY,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_BSPC},
  {KC_GRV,  KC_AMPR, KC_BSLS, KC_LPRN, KC_RPRN, KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL},
  {KC_DEL,  KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______},
  {_______, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______, KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______},
  { AG_NORM, AG_SWAP, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},

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
[_ADJUST] = {
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
  {_______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL},
  {_______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, DVORAK,  _______, _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

};


void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      /*
        case SNEZHI:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_SNEZHI);
          }
          return false;
          break;
          */
        case QWERTY:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_QWERTY);
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_DVORAK);
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
        case SPOTLIGHT:
          if (record->event.pressed) {
              SEND_STRING(SS_DOWN(X_LALT));
              SEND_STRING(SS_DOWN(X_LGUI));
              SEND_STRING(SS_DOWN(X_SPACE));
          } else {
              SEND_STRING(SS_UP(X_LALT));
              SEND_STRING(SS_UP(X_LGUI));
              SEND_STRING(SS_UP(X_SPACE));
          }
          return false;
          break;
        case LANGLANG:
          if (record->event.pressed) {
              SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_SPACE));
          } else {
              SEND_STRING(SS_UP(X_LGUI) SS_UP(X_SPACE));         
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
