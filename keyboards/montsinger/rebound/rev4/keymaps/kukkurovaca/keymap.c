#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
	_BASE,
	_RAISE,
	_LOWER,
	_ADJUST
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE] = LAYOUT_all(
		LCTL_T(KC_ESC)      , KC_Q      , KC_W      , KC_E    , KC_R    , KC_T                 , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , RALT_T(KC_MINS) ,
		LT(_RAISE, KC_TAB)  , KC_A      , KC_S      , KC_D    , KC_F    , KC_G    , KC_NO      , KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , LT(_RAISE, KC_QUOT) ,
		KC_LSFT             , KC_Z      , KC_X      , KC_C    , KC_V    , KC_B    , KC_PSCR    , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , RSFT_T(KC_ENT) ,
		KC_LCTL             , MO(_RAISE), MO(_LOWER),KC_LALT  ,KC_ENT   , KC_BSPC , KC_MUTE , KC_SPC  , KC_RSFT ,MO(_RAISE),KC_RALT , KC_RGUI , RCTL_T(KC_ENT)
	),
	[_RAISE] = LAYOUT_all(
		KC_GRV	, S(KC_1)   , KC_UP      , S(KC_2) , S(KC_4)   , S(KC_5)  ,            S(KC_7) , KC_7    , KC_8    , KC_9    , KC_PAST , KC_PSLS ,
		KC_CAPS	, KC_LEFT   , KC_DOWN    , KC_RIGHT, S(KC_9)   , S(KC_0)  , KC_NO    , S(KC_6) , KC_4    , KC_5    , KC_6    , KC_PMNS , KC_EQL  ,
		KC_TRNS	, S(KC_LBRC), S(KC_RBRC) , S(KC_3) , KC_LBRC   , KC_RBRC  , KC_TRNS  , KC_P0   , KC_1    , KC_2    , KC_3    , KC_PPLS , KC_BSLS ,
		KC_TRNS , KC_TRNS   , KC_TRNS ,MO(_ADJUST),KC_ENT   , KC_DEL      , KC_TRNS  , KC_P0   , KC_P0   , KC_PDOT , KC_PDOT , KC_P0  , KC_BSLS
	),
	[_LOWER] = LAYOUT_all(
		RESET   , G(KC_TAB), KC_F3   , KC_F4   , KC_F5   , KC_F6	      ,              KC_PSCR , KC_VOLU  , KC_HOME , KC_PGUP , KC_F11   , DT_UP  ,
		KC_NO	, C(KC_1)  , C(KC_2) , C(KC_3) , C(KC_4) , C(KC_9)        , KC_NO    ,    KC_NO   , KC_VOLD  , KC_END  , KC_PGDN , KC_NO   , DT_PRNT   ,
		KC_NO   , KC_NO    , KC_NO   , KC_CAPS , KC_NO   , LGUI(KC_DOT)   , KC_TRNS  ,             KC_NO   , KC_MUTE  , KC_NO   , KC_NO   , KC_NO   , DT_DOWN   ,
		KC_TRNS , KC_TRNS  , KC_TRNS , KC_NO   , KC_ENT  , KC_NO          , KC_MUTE  ,    KC_NO   , KC_RSFT  ,MO(_ADJUST),KC_TRNS, KC_TRNS , KC_TRNS
	),
	[_ADJUST] = LAYOUT_all(
		XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX            , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
		XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_CAPS , KC_TRNS  , KC_NLCK , KC_SLCK , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , 
		XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_TRNS  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , 
		KC_TRNS , KC_TRNS , KC_TRNS , XXXXXXX , XXXXXXX , XXXXXXX , KC_MUTE  , XXXXXXX , XXXXXXX , XXXXXXX , KC_TRNS , KC_TRNS , KC_TRNS
	),

};



bool encoder_update_user(uint8_t index, bool clockwise) {
	if(IS_LAYER_ON(_RAISE)){
		if(clockwise){
			tap_code(KC_MS_WH_UP);
		} else {
			tap_code(KC_MS_WH_DOWN);
		}
	} else {
		if(clockwise){
			tap_code(KC_WH_L);
		} else {
			tap_code(KC_WH_R);
		}
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



#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR(""), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("ACAB\n"), false);
	    break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adj\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
}
    oled_write_P(PSTR("\n\n\n\n"), false);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM \n") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS\n") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR \n") : PSTR("    "), false);

    return false;
}

#endif