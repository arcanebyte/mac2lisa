/*
 * keymap.c
 * 
 * Copyright 2019 - James Denton <james.denton@arcanebyte.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 */

/*
 * 
 * (todo) Implement catchall
 */

#include <stdint.h>
#include "keymap.h"
#include "lisakeyslib.h"

// Keymap for M0110 and M0120 (Mac 128k and Mac 512k)
const uint16_t m0110_keymap[] = {

  // Row 1
  [0x32] = LK_TILDE,
	[0x12] = LK_1,
	[0x13] = LK_2,
	[0x14] = LK_3,
	[0x15] = LK_4,
	[0x17] = LK_5,
	[0x16] = LK_6,
	[0x1a] = LK_7,
	[0x1c] = LK_8,
	[0x19] = LK_9,
	[0x1d] = LK_0,
	[0x1b] = LK_MINUS,
	[0x18] = LK_EQUAL,
	[0x33] = LK_BACKSPACE,

  // Row 2
	[0x30] = LK_TAB,
	[0x0c] = LK_Q,
	[0x0d] = LK_W,
	[0x0e] = LK_E,
	[0x0f] = LK_R,
	[0x11] = LK_T,
	[0x10] = LK_Y,
	[0x20] = LK_U,
	[0x22] = LK_I,
	[0x1f] = LK_O,
	[0x23] = LK_P,
	[0x21] = LK_LT_BRACKET,
	[0x1e] = LK_RT_BRACKET,
  [0x2a] = LK_BACKSLASH,

  // Row 3
  [0x39] = LK_CAPS_LOCK,
  [0x00] = LK_A,
  [0x01] = LK_S,
  [0x02] = LK_D,
  [0x03] = LK_F,
  [0x05] = LK_G,
  [0x04] = LK_H,
  [0x26] = LK_J,
  [0x28] = LK_K,
  [0x25] = LK_L,
  [0x29] = LK_SEMICOLON,
  [0x27] = LK_QUOTE,
	[0x24] = LK_RETURN,

  // Row 4
  [0x38] = LK_SHIFT,
  [0x06] = LK_Z,
  [0x07] = LK_X,
  [0x08] = LK_C,
  [0x09] = LK_V,
  [0x0b] = LK_B,
  [0x2d] = LK_N,
  [0x2e] = LK_M,
  [0x2b] = LK_COMMA,
  [0x2f] = LK_PERIOD,
  [0x2c] = LK_SLASH, 
  [0x38] = LK_SHIFT,

  // Row 5
  [0x3a] = LK_LT_OPTION,
  [0x37] = LK_APPLE, 
  [0x31] = LK_SPACE,
  [0x34] = LK_ENTER,
  [0x3a] = LK_LT_OPTION,

  // M0120 Keypad
  
  // Row 1
  [0x47] = LK_NUM_CLEAR,     // 'np clear'
  [0x4e] = LK_NUM_MINUS,     // 'np -',
  [0x46] = LK_NUM_PLUS,      // Left Arrow
  [0x42] = LK_NUM_TIMES,     // Right Arrow

  // Row 2
  [0x59] = LK_NUM_7,          // 'np7',
	[0x5b] = LK_NUM_8,          // 'np8',
	[0x5c] = LK_NUM_9,          // 'np9',
  [0x4d] = LK_NUM_SLASH,      // Up Arrow

  // Row 3
  [0x56] = LK_NUM_4,          // 'np4',
  [0x57] = LK_NUM_5,          // 'np5',
  [0x58] = LK_NUM_6,          // 'np6',
  [0x48] = LK_NUM_COMMA,      // Down Arrow

  // Row 4
  [0x53] = LK_NUM_1, // 'np1',
  [0x54] = LK_NUM_2, // 'np2',
  [0x55] = LK_NUM_3, // 'np3',
  [0x4c] = LK_NUM_ENTER, // 'np enter',

  // Row 5
  [0x52] = LK_NUM_0,      // 'np0',
  [0x41] = LK_NUM_PERIOD, // 'np.',  

};

// Keymap for M0110a (Macintosh Plus)
const uint16_t m0110a_keymap[] = {

  // Row 1
  [0x32] = LK_TILDE,
  [0x12] = LK_1,
  [0x13] = LK_2,
  [0x14] = LK_3,
  [0x15] = LK_4,
  [0x17] = LK_5,
  [0x16] = LK_6,
  [0x1a] = LK_7,
  [0x1c] = LK_8,
  [0x19] = LK_9,
  [0x1d] = LK_0,
  [0x1b] = LK_MINUS,
  [0x18] = LK_EQUAL,
  [0x33] = LK_BACKSPACE,

  // Row 2
  [0x30] = LK_TAB,
  [0x0c] = LK_Q,
  [0x0d] = LK_W,
  [0x0e] = LK_E,
  [0x0f] = LK_R,
  [0x11] = LK_T,
  [0x10] = LK_Y,
  [0x20] = LK_U,
  [0x22] = LK_I,
  [0x1f] = LK_O,
  [0x23] = LK_P,
  [0x21] = LK_LT_BRACKET,
  [0x1e] = LK_RT_BRACKET,

  // Row 3
  [0x39] = LK_CAPS_LOCK,
  [0x00] = LK_A,
  [0x01] = LK_S,
  [0x02] = LK_D,
  [0x03] = LK_F,
  [0x05] = LK_G,
  [0x04] = LK_H,
  [0x26] = LK_J,
  [0x28] = LK_K,
  [0x25] = LK_L,
  [0x29] = LK_SEMICOLON,
  [0x27] = LK_QUOTE,
  [0x24] = LK_RETURN,

  // Row 4
  [0x38] = LK_SHIFT,
  [0x06] = LK_Z,
  [0x07] = LK_X,
  [0x08] = LK_C,
  [0x09] = LK_V,
  [0x0b] = LK_B,
  [0x2d] = LK_N,
  [0x2e] = LK_M,
  [0x2b] = LK_COMMA,
  [0x2f] = LK_PERIOD,
  [0x2c] = LK_SLASH, 
  [0x38] = LK_SHIFT,
  [0x4d] = LK_NUM_SLASH,      // Up Arrow ONLY

  // Row 5
  [0x3a] = LK_LT_OPTION,
  [0x37] = LK_APPLE, 
  [0x31] = LK_SPACE,
  [0x2a] = LK_BACKSLASH,
  [0x46] = LK_NUM_PLUS,      // Left Arrow ONLY
  [0x42] = LK_NUM_TIMES,     // Right Arrow ONLY
  [0x48] = LK_NUM_COMMA,     // Down Arrow ONLY

  // M0110a Keypad
  
  // Row 1
  [0x47] = LK_NUM_CLEAR,     // 'np clear'
  [0x68] = LK_EQUAL,         // 'np ='
  [0x6d] = (LK_MACRO_SHIFT | LK_NUM_SLASH),     // 'np /'
  [0x62] = (LK_MACRO_SHIFT | LK_NUM_TIMES),     // 'np *'

  // Row 2
  [0x59] = LK_NUM_7,          // 'np7',
  [0x5b] = LK_NUM_8,          // 'np8',
  [0x5c] = LK_NUM_9,          // 'np9',
  [0x4e] = LK_NUM_MINUS,      // 'np -',

  // Row 3
  [0x56] = LK_NUM_4,          // 'np4',
  [0x57] = LK_NUM_5,          // 'np5',
  [0x58] = LK_NUM_6,          // 'np6',
  [0x66] = (LK_MACRO_SHIFT | LK_NUM_PLUS), // 'np +'
  
  // Row 4
  [0x53] = LK_NUM_1, // 'np1',
  [0x54] = LK_NUM_2, // 'np2',
  [0x55] = LK_NUM_3, // 'np3',
  [0x4c] = LK_NUM_ENTER, // 'np enter',

  // Row 5
  [0x52] = LK_NUM_0,      // 'np0',
  [0x41] = LK_NUM_PERIOD, // 'np.',  

};
