#include QMK_KEYBOARD_H
#include "keymap_french.h"

enum layers {
    _BASE,
    _LOWER,
    _RAISE,
    _APP,
};

enum custom_keycodes {
    LOWER_APP = SAFE_RANGE,
    APP_BASE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RBRC,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    FR_M,    FR_QUOT,
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE, MO(_RAISE), KC_N,  FR_COMM, FR_SCLN, FR_COLN, FR_EXLM, FR_EQL,
                                   KC_LALT, KC_RALT, KC_LGUI, KC_SPC,     KC_BSPC, KC_ENT,  LOWER_APP, LALT(KC_SPC)
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

    [_APP] = LAYOUT(
        APP_BASE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        LGUI(KC_TAB), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, HYPR(KC_T),              XXXXXXX, XXXXXXX, HYPR(KC_I), XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, HYPR(KC_S), XXXXXXX, HYPR(KC_F), HYPR(KC_G),             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MCTL, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, HYPR(KC_C), XXXXXXX, HYPR(KC_B), LGUI(KC_GRV), LGUI(KC_TAB), XXXXXXX, LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_UP), LCTL(KC_RIGHT), XXXXXXX,
                                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

static uint16_t lower_app_timer;
static bool     lower_app_pressed;
static bool     lower_app_used;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (lower_app_pressed && keycode != LOWER_APP && record->event.pressed) {
        lower_app_used = true;
    }

    switch (keycode) {
        case LOWER_APP:
            if (record->event.pressed) {
                lower_app_timer   = timer_read();
                lower_app_pressed = true;
                lower_app_used    = false;
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
                lower_app_pressed = false;

                if (!lower_app_used && timer_elapsed(lower_app_timer) < TAPPING_TERM) {
                    set_oneshot_layer(_APP, ONESHOT_START);
                    clear_oneshot_layer_state(ONESHOT_PRESSED);
                }
            }
            return false;
        case APP_BASE:
            if (record->event.pressed) {
                reset_oneshot_layer();
                layer_clear();
            }
            return false;
    }

    return true;
}

void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_disable_noeeprom();
#endif
#ifdef RGBLIGHT_ENABLE
    rgblight_disable_noeeprom();
#endif
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _LOWER:
            tap_code(clockwise ? KC_VOLU : KC_VOLD);
            break;
        default:
            tap_code(clockwise ? MS_WHLD : MS_WHLU);
            break;
    }

    return false;
}
#endif

#ifdef OLED_ENABLE
static uint8_t current_layer(void) {
    return get_highest_layer(layer_state | default_layer_state);
}

static bool is_left_display(void) {
#ifdef SPLIT_KEYBOARD
    return is_keyboard_left();
#else
    return is_keyboard_master();
#endif
}

static void render_layer_name(uint8_t layer) {
    switch (layer) {
        case _LOWER:
            oled_write_ln_P(PSTR("LOWER"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("RAISE"), false);
            break;
        case _APP:
            oled_write_ln_P(PSTR("APP  "), false);
            break;
        default:
            oled_write_ln_P(PSTR("BASE "), false);
            break;
    }
}

static void render_layer_row(uint8_t current, uint8_t layer, const char *name) {
    oled_write_ln_P(name, current == layer);
}

static void render_mods(void) {
    uint8_t mods = get_mods() | get_oneshot_mods();

    oled_write_P(PSTR("S"), mods & MOD_MASK_SHIFT);
    oled_write_P(PSTR("C"), mods & MOD_MASK_CTRL);
    oled_write_P(PSTR("A"), mods & MOD_MASK_ALT);
    oled_write_P(PSTR("G"), mods & MOD_MASK_GUI);
    oled_write_ln_P(PSTR(" "), false);
}

static void render_locks(void) {
    led_t led_state = host_keyboard_led_state();

    oled_write_ln_P(PSTR("CAPS "), led_state.caps_lock);
    oled_write_ln_P(PSTR("NUM  "), led_state.num_lock);
}

static void render_left_oled(uint8_t layer) {
    oled_write_ln_P(PSTR("epsxy"), false);
    oled_write_ln_P(PSTR("-----"), false);
    render_layer_row(layer, _BASE, PSTR("BASE "));
    render_layer_row(layer, _LOWER, PSTR("LOWER"));
    render_layer_row(layer, _RAISE, PSTR("RAISE"));
    render_layer_row(layer, _APP, PSTR("APP  "));
    oled_write_ln_P(PSTR("-----"), false);
    oled_write_ln_P(PSTR("MODS "), false);
    render_mods();
    render_locks();
}

static void render_right_oled(uint8_t layer) {
    oled_write_ln_P(PSTR("LAYER"), false);
    oled_write_ln_P(PSTR("-----"), false);
    render_layer_name(layer);
    oled_write_ln_P(PSTR("-----"), false);
    oled_write_ln_P(PSTR("HOLD "), lower_app_pressed);
    oled_write_ln_P(PSTR("APP  "), layer == _APP);
    oled_write_ln_P(PSTR("LOWER"), layer == _LOWER);
    oled_write_ln_P(PSTR("RAISE"), layer == _RAISE);
}

bool oled_task_user(void) {
    static uint8_t last_layer = 255;
    static uint8_t last_mods  = 255;
    static led_t   last_leds  = {0};
    static bool    last_left  = false;
    static bool    last_hold  = false;
    uint8_t        layer      = current_layer();
    uint8_t        mods       = get_mods() | get_oneshot_mods();
    led_t          leds       = host_keyboard_led_state();
    bool           left       = is_left_display();

    if (layer == last_layer && mods == last_mods && leds.raw == last_leds.raw && left == last_left && lower_app_pressed == last_hold) {
        return false;
    }

    last_layer = layer;
    last_mods  = mods;
    last_leds  = leds;
    last_left  = left;
    last_hold  = lower_app_pressed;
    oled_clear();

    if (left) {
        render_left_oled(layer);
    } else {
        render_right_oled(layer);
    }

    return false;
}
#endif
