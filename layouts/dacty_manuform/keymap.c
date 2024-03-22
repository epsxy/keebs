#include QMK_KEYBOARD_H
#include "keymap_french.h"

#define _AZERTY 0
#define _LAYER_1 1
#define _LAYER_2 2

#define AZERTY MO(_AZERTY)
#define LAYER_1 MO(_LAYER_1)
#define LAYER_2 MO(_LAYER_2)

// Tap Dance declarations
enum {
    TD_ESC_L1,
    TD_FR_MINS_LPRN,
    TD_FR_EGRV_RPRN,
    TD_FR_UNDS_LCBR,
    TD_FR_CCED_RCBR,
    TD_FR_AGRV_LBRC,
    TD_FR_RPRN_RBRC,
    TD_C_C,
    TD_P_PCT,
    TD_L_PP,
    TD_N_TLD,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for layer 1
    [TD_ESC_L1] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, TO(LAYER_1)),
    // --- PARENTHESES & MISC
    // Tap once for FR_MINS, twice for (
    [TD_FR_MINS_LPRN] = ACTION_TAP_DANCE_DOUBLE(FR_MINS, FR_LPRN),
    // Tap once for FR_EGRV, twice for )
    [TD_FR_EGRV_RPRN] = ACTION_TAP_DANCE_DOUBLE(FR_EGRV, FR_RPRN),
    // Tap once for FR_UNDS, twice for {
    [TD_FR_UNDS_LCBR] = ACTION_TAP_DANCE_DOUBLE(FR_UNDS, FR_LCBR),
    // Tap once for FR_CCED, twice for }
    [TD_FR_CCED_RCBR] = ACTION_TAP_DANCE_DOUBLE(FR_CCED, FR_RCBR),
    // Tap once for FR_AGRV, twice for [
    [TD_FR_AGRV_LBRC] = ACTION_TAP_DANCE_DOUBLE(FR_AGRV, FR_LBRC),
    // Tap once for FR_RPRN, twice for ]
    [TD_FR_RPRN_RBRC] = ACTION_TAP_DANCE_DOUBLE(FR_RPRN, FR_RBRC),
   
    // --- SHORTCUTS ON LETTERS
    // Tap once for C, twice for ç
    [TD_C_C] = ACTION_TAP_DANCE_DOUBLE(FR_C, FR_CCED),
    // Tap once for P, twice for %
    [TD_P_PCT] = ACTION_TAP_DANCE_DOUBLE(FR_P, FR_PERC),
    // Tap once for L, twice for |
    [TD_L_PP] = ACTION_TAP_DANCE_DOUBLE(FR_L, FR_PIPE),
    // Tap once for N, twice for tilde
    [TD_N_TLD] = ACTION_TAP_DANCE_DOUBLE(FR_N, FR_TILD),
};

// ---------------------------------------------------- TAP HOLD ----------------------------------------------------
// TODO: implement
// ------------------------------------------------------------------------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_AZERTY] = LAYOUT_5x6(
     // ESC/L1    , &      , é      , "      , '      , (      ,                     -      , è      , _      , ç      , à      , )      ,
        TD(TD_ESC_L1), FR_AMPR, FR_EACU, FR_DQUO, FR_QUOT, FR_LPRN,               TD(TD_FR_MINS_LPRN), TD(TD_FR_EGRV_RPRN), TD(TD_FR_UNDS_LCBR), TD(TD_FR_CCED_RCBR), TD(TD_FR_AGRV_LBRC), TD(TD_FR_RPRN_RBRC),
     // TAB    , A     , Z      , E     , R     , T     ,                         Y     , U       , I     , O     , P     , $
        KC_TAB , FR_A  , FR_Z   , FR_E  , FR_R  , FR_T  ,                         FR_Y  , FR_U   , FR_I  , FR_O  , FR_P  , FR_DLR,
     // LSHIFT , Q     , S      , D    , F     , G     ,                          H     , J      , K      , L   , M      , ù
        KC_LSFT, FR_Q  , FR_S   , FR_D  , FR_F  , FR_G  ,                         FR_H  , FR_J   , FR_K   , FR_L , FR_M   , FR_UGRV,
     // CTLR   , W     , X      , C      , V     , B     ,                        N     , `,`    , ;      , :      , !      , *       ,
        KC_LCTL, FR_W  , FR_X   , FR_C   , FR_V  , FR_B  ,                        FR_N  , FR_COMM, FR_SCLN, FR_COLN, FR_EXLM, FR_ASTR ,
                      // LALT   , LSUPER ,                                                         RLAT   , =
                         KC_LALT, KC_LGUI,                                                         KC_RALT, FR_EQL,
                             // SPC   ,  BSPC        ,                                     DEL   , ENTER  ,
                                KC_SPC, KC_BSPC      ,                                     KC_DEL, KC_ENT ,
                      // BOTTOM RIGHT (OSX SCREEN), TOP RIGHT              // TOP LEFT, BOTTOM LEFT
                         LCTL(LSFT(LGUI(FR_QUOT))), TO(LAYER_1),                 TO(LAYER_2) ,LCTL(LSFT(LGUI(FR_QUOT))),
                                     // BOTTOM LEFT, TOP LEFT              // TOP RIGHT, BOTTOM RIGHT
                                        LCA(KC_SPC), OSL(LAYER_1),            OSL(LAYER_2),LCA(KC_SPC)
    ),
    [_LAYER_1] = LAYOUT_5x6(
        TD_ESC_L1 , KC_F1  , KC_F2  , KC_F3   , KC_F4 , KC_F5 ,                         KC_F6  , KC_F7 , KC_F8 , KC_F9 , KC_F10, KC_F11,
        _______,_______ , KC_UP  , FR_CIRC ,_______,_______,                         _______,_______,FR_DIAE,_______,_______, KC_F12,
        _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______,_______,                         _______,_______,_______,_______,_______,_______,
        _______,_______ ,FR_LABK ,FR_RABK  ,_______,_______,                         FR_TILD,_______,_______,_______,_______,_______,
                         _______ ,_______  ,                                                          _______,_______,
                                  _______  ,_______   ,                                       _______,_______,
                                          _______,TO(AZERTY),                         _______,_______,
                                          _______,_______   ,                         _______,_______
    ),
    [_LAYER_2] = LAYOUT_5x6(
     // _______,_______,_______,_______,_______,_______,                         (      , )     , {     , }     , [     , ]     ,
      TD_ESC_L1,_______,_______,_______,_______,_______,                         FR_LPRN,FR_RPRN,FR_LCBR,FR_RCBR,FR_LBRC,FR_RBRC,
     // _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
        _______, FR_AT ,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,FR_PERC,
     // _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,                         FR_HASH,FR_GRV ,FR_BSLS,FR_PIPE,_______,_______,
        _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
                         _______,_______,                                                        FR_LABK,FR_RABK,
                                 _______,_______,                                        _______,_______,
                                         _______,_______,                     TO(AZERTY),_______,
                                         _______,_______,                        _______,_______
    ),
/*
   [_LAYER_2] = LAYOUT_5x6(
        _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______, 
        _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
                        _______,_______,                                                         _______,_______,
                                  _______,_______,                                       _______,_______,
                                          _______,_______,                         _______,_______,
                                          _______,_______,                         _______,_______
    ),
*/
};