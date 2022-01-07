/* Copyright 2021 Brandon Lewis
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

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x666B // fk
#define PRODUCT_ID      0x7273 // rs
#define DEVICE_VER      0x0001 // rev 1
#define MANUFACTURER    fruitykeeb
#define PRODUCT         ristretto

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 13

/* key matrix pins */
#define MATRIX_ROW_PINS { B1, B2, B3, D3 }
#define MATRIX_COL_PINS { C7, C6, B6, B5, B4, D7, B7, F0, F1, F4, F5, F6, F7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Default resolution is 4 */

#define ENCODERS_PAD_A { D4 }
#define ENCODERS_PAD_B { D6 }
#define ENCODER_RESOLUTION 3

/* Tap-hold configuration settings */
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM 135
#define TAPPING_FORCE_HOLD
#define RETRO_TAPPING
#define TAPPING_TERM_PER_KEY