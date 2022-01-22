/* Copyright 2018 'Masayuki Sunahara'
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
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST
};

#define CTL_TAB CTL_T(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x7_4(
        LCTL_T(KC_ESC)    , KC_Q   , KC_W   , KC_E    , KC_R     , KC_T   , KC_LPRN  ,    KC_RPRN, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , RALT_T(KC_MINS)  ,
        LT(_LOWER, KC_TAB), KC_A   , KC_S   , KC_D    , KC_F     , KC_G   , KC_LBRC  ,    KC_RBRC, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, LT(_LOWER, KC_QUOT)   ,
        KC_LSFT           , KC_Z     , KC_X   , KC_C    , KC_V     , KC_B   , LOWER    ,    RAISE  , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, RSFT_T(KC_ENT) ,
                                   KC_LCTRL, KC_LGUI  , KC_LALT, KC_BSPACE,    KC_ENT , KC_SPC , LOWER  , RCTL_T(KC_ENT)
    ),
    [_LOWER] = LAYOUT_split_3x7_4(
        KC_GRV , S(KC_1), KC_UP  , S(KC_2) , S(KC_4)   , S(KC_5)   , _______,    _______, S(KC_7), KC_7   , KC_8   , KC_9   , KC_PAST, KC_PSLS,
        _______, KC_LEFT, KC_DOWN, KC_RIGHT, S(KC_9)   , S(KC_0)   , _______,    _______, S(KC_6), KC_4   , KC_5   , KC_6   , KC_PMNS, KC_EQL ,
        _______, KC_LBRC, KC_RBRC, S(KC_3) , S(KC_LBRC), S(KC_RBRC), _______,    _______, KC_GRV , KC_1   , KC_2   , KC_3   , KC_PPLS, KC_BSLS,
                                   _______, _______, _______, KC_DEL,    KC_P0, KC_P0 , KC_PDOT, KC_PDOT
    ),
    [_RAISE] = LAYOUT_split_3x7_4(
        RESET  , G(KC_TAB), _______, _______, _______, A(KC_F4)     , _______,    _______, KC_PSCR, KC__VOLUP  , KC_HOME, KC_PGUP, KC_F11 , DT_UP  ,
        RCG_SWP, C(KC_1)  , C(KC_2), C(KC_3), C(KC_4), C(KC_9)      , _______,    _______, _______, KC__VOLDOWN, KC_END , KC_PGDN, KC_WH_U, DT_PRNT,
        RCG_NRM, _______  , _______, KC_CAPS, _______, LGUI(KC_DOT) , _______,    _______, _______, KC__MUTE   , KC_WH_L, KC_WH_R, KC_WH_D, DT_DOWN,
                                     _______, _______, _______ , _______,    _______, _______, _______, _______
    ),
    [_ADJUST] = LAYOUT_split_3x7_4(
        _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_LCBR,    KC_RCBR, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______,
        _______, KC_F11 , KC_F12 , _______, _______, _______, KC_LCBR,    KC_RCBR, KC_HOME, KC_PGDN, KC_PGUP, KC_END , _______, _______,
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______,    _______, _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // set_timelog();
    }

    switch (keycode) {
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
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
    }
    return true;
}


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