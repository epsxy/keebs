#include QMK_KEYBOARD_H
#include "keymap_french.h"

enum layers {
    _BASE,
    _LOWER,
    _RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RBRC,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    FR_M,    FR_QUOT,
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    MO(_LOWER), MO(_RAISE), KC_N,  FR_COMM, FR_SCLN, FR_COLN, FR_EXLM, FR_EQL,
                                   KC_LALT, KC_RALT, KC_LGUI, KC_SPC,     KC_BSPC, KC_ENT,  XXXXXXX, LALT(KC_SPC)
    ),

    [_LOWER] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_TAB,  XXXXXXX, XXXXXXX, FR_CIRC, FR_DIAE, XXXXXXX,                      FR_LPRN, FR_RPRN, FR_LCBR, FR_RCBR, FR_LBRC, FR_RBRC,
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      FR_HASH, FR_AMPR, FR_ASTR, FR_PIPE, FR_PERC, XXXXXXX,
        KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    FR_TILD, FR_LABK, FR_RABK, XXXXXXX, XXXXXXX, LCTL(KC_UP),
                                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_DEL,  XXXXXXX, LCTL(KC_LEFT), LCTL(KC_RIGHT)
    ),

    [_RAISE] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_VOLU, KC_VOLD, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
        XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, LCTL(RALT(KC_SPC)),           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LCTL(LSFT(LGUI(FR_QUOT))), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_write_ln_P(PSTR("Aurora"), false);
    oled_write_ln_P(PSTR("Lily58"), false);

    switch (get_highest_layer(layer_state)) {
        case _LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Base"), false);
            break;
    }

    return false;
}
#endif
