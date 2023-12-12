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



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    LCTL_T(KC_ESC)    ,  KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     RALT_T(KC_MINS),
    LT(_RAISE, KC_TAB),  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  LT(_RAISE, KC_QUOT),
    KC_LSFT           ,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  RSFT_T(KC_ENT),
                                            KC_LALT,   KC_BSPC,  MO(_ADJUST),  KC_SPC ,    RCTL_T(KC_ENT)
  ),

  [_LOWER] = LAYOUT(
		QK_BOOT , G(KC_TAB), KC_F3   , KC_F4   , KC_F5   , KC_F6	         ,    KC_PSCR , KC_VOLU  , KC_HOME , KC_PGUP , KC_F11   , DT_UP  ,
		CG_RSWP	, C(KC_1)  , C(KC_2) , C(KC_3) , C(KC_4) , C(KC_9)           ,    KC_NO   , KC_VOLD  , KC_END  , KC_PGDN , KC_WH_U   , DT_PRNT   ,
		CG_RNRM , RGB_TOG  , _______   , KC_CAPS , KC_NO   , LGUI(KC_DOT)    ,    KC_NO   , KC_MUTE  , KC_WH_L   , KC_WH_R   , KC_WH_D   , DT_DOWN   ,
                                            _______,   OSL(_ADJUST),  XXXXXXX,   _______,  _______
  ),

  [_RAISE] = LAYOUT(
		KC_GRV	, S(KC_1)   , KC_UP      , S(KC_2) , S(KC_4)   , S(KC_5)        , S(KC_7) , KC_7    , KC_8    , KC_9    , KC_PAST , KC_PSLS ,
		KC_CAPS	, KC_LEFT   , KC_DOWN    , KC_RIGHT, S(KC_9)   , S(KC_0)        , S(KC_6) , KC_4    , KC_5    , KC_6    , KC_PMNS , KC_EQL  ,
		KC_TRNS	, S(KC_LBRC), S(KC_RBRC) , S(KC_3) , KC_LBRC   , KC_RBRC        , KC_F2   , KC_1    , KC_2    , KC_3    , KC_PPLS , KC_BSLS ,
                                            OSL(_LOWER),   KC_DEL,  XXXXXXX, KC_P0,  KC_PDOT
  ),

  [_ADJUST] = LAYOUT(
    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  XXXXXXX,   RGB_TOG,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            QK_BOOT,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
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






// Thumbstick keymap, change KC_XXX to whatever you need

#define THUMBSTICK_RIGHT_TAP KC_RIGHT
#define THUMBSTICK_LEFT_TAP KC_LEFT
#define THUMBSTICK_UP_TAP KC_UP
#define THUMBSTICK_DOWN_TAP KC_DOWN

// Thumbstick code, no customisation needed

bool cursor_mode = false;
bool scrolling_mode = false;
bool tapping_mode = false;

// tracks if thumbstick was released
bool returned_to_zero = true;

// tracks how many times mouse_report.x/y have been read zero in succession
uint16_t zero_reads = 0;

// set mode depending on layer
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    switch (get_highest_layer(state)) {
        case SCROLLING_LAYER:
            if (scrolling_mode == false) {
            scrolling_mode = true;
            }
            if (tapping_mode) {
                tapping_mode = false;
            }
            if (cursor_mode) {
                cursor_mode = false;
            }
            break;
        case TAPPING_LAYER:
            if (tapping_mode == false) {
                tapping_mode = true;
            }
            if (cursor_mode) {
                cursor_mode = false;
            }
            if (scrolling_mode) {
                scrolling_mode = false;
            }
            break;
        default:
            if (tapping_mode == false) {
                tapping_mode = true;
            }
            if (cursor_mode) {
                cursor_mode = false;
            }
            if (scrolling_mode) {
                scrolling_mode = false;
            }
            break;
    }
    return state;
}

// manipulate mouse report based on current mode
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {

    if (cursor_mode) {
        mouse_report.x = CURSOR_SPEED * mouse_report.x/100;
        mouse_report.y = CURSOR_SPEED * mouse_report.y/100;
    }
    if (scrolling_mode) {
        mouse_report.h = SCROLL_SPEED * mouse_report.x/100;
        mouse_report.v = SCROLL_SPEED * mouse_report.y/100;
        mouse_report.x = 0;
        mouse_report.y = 0;
        if ((mouse_report.h != 0) | (mouse_report.v != 0)) {
            _delay_ms(SCROLL_DELAY_MS);
        }

    } else if (tapping_mode) {
        if ((mouse_report.x || mouse_report.y) != 0) {
            if (returned_to_zero) {
                if (mouse_report.x > 0) {
                    tap_code16(THUMBSTICK_RIGHT_TAP);
                }
                if (mouse_report.x < 0) {
                    tap_code16(THUMBSTICK_LEFT_TAP);
                }
                if (mouse_report.y > 0) {
                    tap_code16(THUMBSTICK_DOWN_TAP);
                }
                if (mouse_report.y < 0) {
                    tap_code16(THUMBSTICK_UP_TAP);
                }
                returned_to_zero = false;
            }
            zero_reads = 0;
        } else if (zero_reads < 20) {
            zero_reads++;
        }
        if (zero_reads >= 20) {
            if (returned_to_zero == false) {
                returned_to_zero = true;
            }
        }
        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    return mouse_report;
}