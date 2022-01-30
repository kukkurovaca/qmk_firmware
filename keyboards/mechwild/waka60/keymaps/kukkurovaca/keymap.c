/* Copyright 2021 Kyle McCreery
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _ADJUST,
	_RAISE,
	_LOWER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
    KC_GRV              , KC_1      , KC_2      , KC_3    , KC_4    , KC_5,               KC_6    , KC_7    , KC_8     , KC_9    , KC_0    ,   KC_BSLS,
    LCTL_T(KC_ESC)      , KC_Q      , KC_W      , KC_E    , KC_R    , KC_T,               KC_Y    , KC_U    , KC_I     , KC_O    , KC_P    ,   RALT_T(KC_MINS)     ,
    LT(_RAISE, KC_TAB)  , KC_A      , KC_S      , KC_D    , KC_F    , KC_G,               KC_H    , KC_J    , KC_K     , KC_L    , KC_SCLN ,   LT(_RAISE, KC_QUOT) ,
    KC_LSFT             , KC_Z      , KC_X      , KC_C    , KC_V    , KC_B,   KC_MUTE,    KC_N    , KC_M    , KC_COMM  , KC_DOT  , KC_SLSH ,   RSFT_T(KC_ENT)      ,
    KC_LCTL             , MO(_RAISE), MO(_LOWER), KC_LALT , KC_BSPC , KC_DEL, KC_PSCR,    KC_ENT  , KC_SPC  , MO(_RAISE), KC_RALT , KC_RGUI ,  RCTL_T(KC_ENT)
    ),
    [_ADJUST] = LAYOUT(                                                                                   
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,            KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
    KC_TRNS, AU_TOG,  RGB_TOG, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, MU_TOG,  RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, MU_MOD,  RGB_RMOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_RAISE] = LAYOUT(                                                                                   
    KC_TRNS , KC_TRNS   , KC_TRNS    , KC_TRNS , KC_TRNS   , KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS ,
    KC_GRV	, S(KC_1)   , KC_UP      , S(KC_2) , S(KC_4)   , S(KC_5),          S(KC_7), KC_7   , KC_8   , KC_9   , KC_PAST, KC_PSLS ,
    KC_CAPS	, KC_LEFT   , KC_DOWN    , KC_RIGHT, S(KC_9)   , S(KC_0),          S(KC_6), KC_4   , KC_5   , KC_6   , KC_PMNS, KC_EQL  ,
    KC_TRNS	, S(KC_LBRC), S(KC_RBRC) , S(KC_3) , KC_LBRC   , KC_RBRC, KC_TRNS, KC_P0  , KC_1   , KC_2   , KC_3   , KC_PPLS, KC_BSLS ,
    KC_TRNS , KC_TRNS   , KC_TRNS    , KC_TRNS , KC_TRNS   , KC_TRNS, MO(_ADJUST), KC_P0  , KC_P0  , KC_PDOT, KC_PDOT, KC_P0  , KC_BSLS
    ),
    [_LOWER] = LAYOUT(      
    KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS      ,          KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                                                                                 
    RESET   , G(KC_TAB), KC_F3   , KC_F4   , KC_F5   , KC_F6	    ,          KC_PSCR , KC_VOLU  , KC_HOME , KC_PGUP , KC_F11  , DT_UP   ,
    KC_NO	, C(KC_1)  , C(KC_2) , C(KC_3) , C(KC_4) , C(KC_9)      ,          KC_NO   , KC_VOLD  , KC_END  , KC_PGDN , KC_WH_U   , DT_PRNT  ,
    KC_NO   , KC_NO    , KC_NO   , KC_CAPS , KC_NO   , LGUI(KC_DOT) , KC_TRNS,  KC_NO   , KC_MUTE  , KC_WH_L, KC_WH_R , KC_WH_D   , DT_DOWN  ,
    KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS      , KC_TRNS, KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
    )
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

