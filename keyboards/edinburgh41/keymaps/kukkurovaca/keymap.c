/* Copyright 2020 @toastedmangoes
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

#include "keycodes.h"

#ifdef THUMBSTICK_ENABLE
#    include "thumbstick.h"
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung41(
    LCTL_T(KC_ESC)    ,  KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     RALT_T(KC_MINS),
    LT(_RAISE, KC_TAB),  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  LT(_RAISE, KC_QUOT),
    KC_LSFT           ,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  RSFT_T(KC_ENT),
                                            KC_LALT,   KC_BSPC,  MO(_LOWER),  KC_SPC ,    RCTL_T(KC_ENT)
  ),

  [_LOWER] = LAYOUT_reviung41(
		RESET   , G(KC_TAB), KC_F3   , KC_F4   , KC_F5   , KC_F6	         ,    KC_PSCR , KC_VOLU  , KC_HOME , KC_PGUP , KC_F11   , DT_UP  ,
		RCG_SWP	, C(KC_1)  , C(KC_2) , C(KC_3) , C(KC_4) , C(KC_9)           ,    KC_NO   , KC_VOLD  , KC_END  , KC_PGDN , KC_WH_U   , DT_PRNT   ,
		RCG_NRM , RGB_TOG  , KC_NO   , KC_CAPS , KC_NO   , LGUI(KC_DOT)    ,    KC_NO   , KC_MUTE  , KC_WH_L   , KC_WH_R   , KC_WH_D   , DT_DOWN   ,
                                            _______,   MO(_ADJUST),  KC_ENT,   _______,  _______
  ),

  [_RAISE] = LAYOUT_reviung41(
		KC_GRV	, S(KC_1)   , KC_UP      , S(KC_2) , S(KC_4)   , S(KC_5)        , S(KC_7) , KC_7    , KC_8    , KC_9    , KC_PAST , KC_PSLS ,
		KC_CAPS	, KC_LEFT   , KC_DOWN    , KC_RIGHT, S(KC_9)   , S(KC_0)        , S(KC_6) , KC_4    , KC_5    , KC_6    , KC_PMNS , KC_EQL  ,
		KC_TRNS	, S(KC_LBRC), S(KC_RBRC) , S(KC_3) , KC_LBRC   , KC_RBRC        , KC_P0   , KC_1    , KC_2    , KC_3    , KC_PPLS , KC_BSLS ,
                                            MO(_LOWER),   KC_DEL,  KC_BSPC,  KC_P0,  KC_PDOT
  ),

  [_ADJUST] = LAYOUT_reviung41(
    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  XXXXXXX,   RGB_TOG,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            RESET,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                            _______,   _______,  XXXXXXX,  _______,  _______
  ),
};

// Setting a longer tapping for - and ', since otherwise it's hard to get those tap values at some typing speeds. 


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RALT_T(KC_MINS):
            return TAPPING_TERM + 65;
        case LT(_RAISE, KC_QUOT):
            return TAPPING_TERM + 65;
        default:
            return TAPPING_TERM;
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {

#ifdef THUMBSTICK_ENABLE
        case TMB_MODE:
            if (record->event.pressed) {
                thumbstick_mode_cycle_forward();
            }
#endif
    }
    return true;
}

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_WHITE);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
#endif
