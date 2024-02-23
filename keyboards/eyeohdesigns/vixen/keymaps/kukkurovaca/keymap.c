/* Copyright 2021 sekigon-gonnoc
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

// Defines the keycodes used by our macros in process_record_user

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [0] = LAYOUT(
        LCTL_T(KC_ESC), 	 KC_Q,    KC_W,    KC_E,      KC_R,       KC_T,    KC_Y,    KC_U,    KC_I,      KC_O,     KC_P,    RALT_T(KC_MINS),
        LT(1, KC_TAB), 		 KC_A,    KC_S,    KC_D,      KC_F,       KC_G,    KC_H,    KC_J,    KC_K,      KC_L,     KC_SCLN, LT(1, KC_QUOT),
        KC_LSFT,			 KC_Z,    KC_X,    KC_C,      KC_V,       KC_B,    KC_N,    KC_M,    KC_COMM,   KC_DOT,   KC_SLSH, RSFT_T(KC_ENT),
        KC_LCTL,                	   KC_LALT, KC_BSPC,  MO(2),    KC_LGUI, KC_SPC,  KC_RCTL,              			       KC_ENT
    ),
	
	[1] = LAYOUT(
	    KC_GRV,  S(KC_1),      KC_UP,     S(KC_2),  S(KC_4), S(KC_5),           S(KC_7),  KC_P7,   KC_P8,   KC_P9,  KC_PAST, KC_PSLS,
		 KC_CAPS, KC_LEFT,      KC_DOWN,   KC_RGHT,  S(KC_9), S(KC_0),          S(KC_6), KC_P4,   KC_P5,   KC_P6,   KC_PMNS, KC_EQL,
		KC_TRNS, S(KC_LBRC),   S(KC_RBRC), S(KC_3), KC_LBRC, KC_RBRC,  		    KC_F2,  KC_P1,   KC_P2,   KC_P3,   KC_PPLS, KC_BSLS,
		_______,                			  _______,KC_DEL, KC_DEL,			KC_P0, KC_P0,  KC_PDOT,                  _______
	),

   [2] = LAYOUT(
	    QK_BOOT ,G(KC_TAB),   KC_F3, KC_HASH,  KC_F4,    KC_F6,                      KC_PSCR, KC_VOLU, KC_HOME, KC_PGUP, KC_F11 ,   DT_UP,
		KC_TRNS, C(KC_1), C(KC_2), C(KC_3), C(KC_4), C(KC_9),                      KC_TRNS, KC_VOLD, KC_END,  KC_PGDN, KC_TRNS, DT_PRNT,
		KC_TRNS,  KC_TRNS, KC_TRNS, KC_CAPS, KC_TRNS, KC_TRNS,                      KC_TRNS, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, DT_DOWN,
		_______,                  _______,_______, _______,_______, _______,_______,                  _______
	),
	
	[3] = LAYOUT(
	    _______, _______,_______, _______,_______, _______,_______, _______,_______, _______,_______, _______,
		_______, _______,_______, _______,_______, _______,_______, _______,_______, _______,_______, _______,
		_______, _______,_______, _______,_______, _______,_______, _______,_______, _______,_______, _______,
		_______,                  _______,_______, _______,_______, _______,_______,                  _______
	),
};


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RALT_T(KC_MINS):
            return TAPPING_TERM + 65;
        case LT(1, KC_QUOT):
            return TAPPING_TERM + 65;
        default:
            return TAPPING_TERM;
    }
}