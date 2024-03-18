#include QMK_KEYBOARD_H
#include "keymap_french.h"

#define _AZERTY 0
#define _LAYER_1 1
#define _LAYER_2 2

#define AZERTY MO(_AZERTY)
#define LAYER_1 MO(_LAYER_1)
#define LAYER_2 MO(_LAYER_2)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_AZERTY] = LAYOUT_5x6(
     // ESC    , &      , é      , "      , '      , (      ,                     -      , è      , _      , ç      , à      , )      ,
        KC_ESC , FR_AMPR, FR_EACU, FR_DQUO, FR_QUOT, FR_LPRN,                     FR_MINS, FR_EGRV, FR_UNDS, FR_CCED, FR_AGRV, FR_RPRN,
     // TAB    , A     , Z      , E     , R     , T     ,                         Y    , U       , I     , O     , P     , $
        KC_TAB , FR_A  , FR_Z   , FR_E  , FR_R  , FR_T  ,                         FR_Y  , FR_U   , FR_I  , FR_O  , FR_P  , FR_DLR,
     // LSHIFT , Q     , S      , D    , F     , G     ,                          H     , J      , K      , L   , M      , ù
        KC_LSFT, FR_Q  , FR_S   , FR_D  , FR_F  , FR_G  ,                         FR_H  , FR_J   , FR_K   , FR_L, FR_M   , FR_UGRV,
     // CTLR   , W     , X      , C      , V     , B     ,                        N     , `,`    , ;      , :      , !      , *       ,
        KC_LCTL, FR_W  , FR_X   , FR_C   , FR_V  , FR_B  ,                        FR_N  , FR_COMM, FR_SCLN, FR_COLN, FR_EXLM, FR_ASTR ,
                      // LALT   , LSUPER ,                                                         RLAT   , =
                         KC_LALT, KC_LGUI,                                                         KC_RALT, FR_EQL,
                             // SPC   ,  BSPC        ,                                     DEL   , ENTER  ,
                                KC_SPC, KC_BSPC      ,                                     KC_DEL, KC_ENT ,
                                     // BOTTOM RIGHT, TOP RIGHT            // TOP LEFT, BOTTOM LEFT
                         LCTL(LSFT(LGUI(FR_QUOT))), TO(LAYER_1),                 TO(LAYER_2) ,LCTL(LSFT(LGUI(FR_QUOT))),
                                     // BOTTOM LEFT, TOP LEFT              // TOP RIGHT, BOTTOM RIGHT
                                        LCA(KC_SPC), OSL(LAYER_1),            OSL(LAYER_2),LCA(KC_SPC)
    ),
    [_LAYER_1] = LAYOUT_5x6(
        KC_ESC , KC_F1  , KC_F2  , KC_F3   , KC_F4 , KC_F5 ,                         KC_F6  , KC_F7 , KC_F8 , KC_F9 , KC_F10, KC_F11,
        _______,_______ , KC_UP  , FR_CIRC ,_______,_______,                         _______,_______,FR_DIAE,_______,_______, KC_F12,
        _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______,_______,                         _______,_______,_______,_______,_______,_______,
        _______,_______ ,_______ ,_______  ,_______,_______,                         FR_TILD,_______,_______,_______,_______,_______,
                         FR_LABK ,FR_RABK  ,                                                          _______,_______,
                                  _______  ,_______   ,                                       _______,_______,
                                          _______,TO(AZERTY),                         _______,_______,
                                          _______,_______   ,                         _______,_______
    ),
    [_LAYER_2] = LAYOUT_5x6(
     // _______,_______,_______,_______,_______,_______,                         (      , )     , {     , }     , [     , ]     ,
        _______,_______,_______,_______,_______,_______,                         FR_LPRN,FR_RPRN,FR_LCBR,FR_RCBR,FR_LBRC,FR_RBRC,
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
/*     [_LAYER_2] = LAYOUT_5x6(
        _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______, 
        _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
                        _______,_______,                                                         _______,_______,
                                  _______,_______,                                       _______,_______,
                                          _______,_______,                         _______,_______,
                                          _______,_______,                         _______,_______
    ), */
};