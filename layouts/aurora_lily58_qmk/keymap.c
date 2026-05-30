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
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE, MO(_RAISE), KC_N,  FR_COMM, FR_SCLN, FR_COLN, FR_EXLM, FR_EQL,
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
static const uint8_t PROGMEM digit_glyphs[][7] = {
    {0b00100, 0b01100, 0b00100, 0b00100, 0b00100, 0b00100, 0b01110},
    {0b01110, 0b10001, 0b00001, 0b00010, 0b00100, 0b01000, 0b11111},
    {0b11110, 0b00001, 0b00001, 0b01110, 0b00001, 0b00001, 0b11110},
};

static uint8_t current_layer(void) {
    return get_highest_layer(layer_state | default_layer_state);
}

static uint8_t layer_number(uint8_t layer) {
    switch (layer) {
        case _LOWER:
            return 2;
        case _RAISE:
            return 3;
        default:
            return 1;
    }
}

static void draw_scaled_digit(uint8_t digit, uint8_t x, uint8_t y, uint8_t scale) {
    if (digit < 1 || digit > 3) {
        return;
    }

    for (uint8_t row = 0; row < 7; row++) {
        uint8_t bits = pgm_read_byte(&digit_glyphs[digit - 1][row]);

        for (uint8_t col = 0; col < 5; col++) {
            if (!(bits & (1 << (4 - col)))) {
                continue;
            }

            for (uint8_t dy = 0; dy < scale; dy++) {
                for (uint8_t dx = 0; dx < scale; dx++) {
                    oled_write_pixel(x + (col * scale) + dx, y + (row * scale) + dy, true);
                }
            }
        }
    }
}

static void draw_art_square(uint8_t x, uint8_t y, uint8_t size) {
    for (uint8_t row = 0; row < size; row++) {
        for (uint8_t col = 0; col < size; col++) {
            bool border = row == 0 || col == 0 || row == size - 1 || col == size - 1;
            bool weave  = ((row + col) % 5) == 0 || ((row + (size - col)) % 7) == 0;

            oled_write_pixel(x + col, y + row, border || weave);
        }
    }
}

static void draw_art_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
    for (uint8_t row = 0; row < height; row++) {
        for (uint8_t col = 0; col < width; col++) {
            bool border = row == 0 || col == 0 || row == height - 1 || col == width - 1;
            bool trace  = ((col + (row * 2)) % 9) == 0 || (((width - col) + row) % 13) == 0;

            oled_write_pixel(x + col, y + row, border || trace);
        }
    }
}

static bool is_left_display(void) {
#ifdef SPLIT_KEYBOARD
    return is_keyboard_left();
#else
    return is_keyboard_master();
#endif
}

static void render_left_oled(uint8_t number) {
    oled_set_cursor(8, 0);
    oled_write_P(PSTR("epsxy"), false);
    draw_scaled_digit(number, 56, 9, 3);
    draw_art_square(4, 13, 18);
}

static void render_right_oled(uint8_t number) {
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("L"), false);
    oled_write_char('0' + number, true);
    draw_art_rect(18, 8, 104, 22);
}

bool oled_task_user(void) {
    static uint8_t last_number = 0;
    static bool    last_left   = false;
    uint8_t        number      = layer_number(current_layer());
    bool           left        = is_left_display();

    if (number == last_number && left == last_left) {
        return false;
    }

    last_number = number;
    last_left   = left;
    oled_clear();

    if (left) {
        render_left_oled(number);
    } else {
        render_right_oled(number);
    }

    return false;
}
#endif
