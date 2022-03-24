/*
 * mac2lisa.ino
 * 
 * Copyright 2020 - James Denton <james.denton@arcanebyte.com>
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
 * Converts M0110/M0120/M0110A protocol to Apple Lisa protocol.
 * 
 * This project would not have been possible without the excellent work of
 * RebeccaRGB and her LisaKeys project: https://github.com/RebeccaRGB/lisakeys
 * along with others at TMK: https://github.com/tmk/tmk_keyboard
 *
 * Useful documentation:
 * http://www.bitsavers.org/pdf/apple/lisa/hardware/Lisa_Hardware_Reference_Manual_Jul81.pdf
 * http://bitsavers.trailing-edge.com/pdf/apple/lisa/hardware/Lisa_Hardware_Manual_Sep82.pdf
 * https://lisa.sunder.net/LisaHardwareManual1983.pdf
 * http://www.mac.linux-m68k.org/devel/plushw.php
 * http://www.synack.net/~bbraun/mackbd/index.html
 * 
 * Keyboard init can return the following models:
 * 
 * [0x03] Macintosh 128k/512k keyboard (no keypad)
 * [0x13] Macintosh 128k/512k keyboard w/ number keypad
 * [0x0B] Macintosh Plus keyboard w/ built-in number keypad
 * 
 */

/* 
 * To debug, uncomment serial lines
 */

#include "keymap.h"
#include "lisakeyslib.h"
#include "m0110.h"
#include "matrix.h"

/* ports */
#define M0110_CLOCK_PORT        PORTD
#define M0110_CLOCK_PIN         PIND
#define M0110_CLOCK_DDR         DDRD
#define M0110_CLOCK_BIT         1
#define M0110_DATA_PORT         PORTD
#define M0110_DATA_PIN          PIND
#define M0110_DATA_DDR          DDRD
#define M0110_DATA_BIT          0

#define ADB_PORT PORTD
#define ADB_DDR DDRD
#define ADB_INPUT PIND
#define ADB_PIN 4

#define DEBUG 0

uint8_t keybrd_model = m0110_model_query();    // Find the model number of the keyboard we're talking to

static void print_u8( uint8_t x )
{
	Serial.print((x >> 4) & 0xF, HEX);
	Serial.print((x >> 0) & 0xF, HEX);
}


static unsigned char get_layout_setting() {
  // Default to US keyboard layout
  pinMode(LK_KB_SETTING_1, INPUT_PULLUP);
  pinMode(LK_KB_SETTING_2, INPUT_PULLUP);
  if (!digitalRead(LK_KB_SETTING_1)) {
    // If jumper 1 is LOW, then...
    // return US layout if jumper 2 is also LOW
    // otherwise, return UK layout (e.g. jumper 2 is HIGH)
    return digitalRead(LK_KB_SETTING_2)
         ? LK_LAYOUT_UK : LK_LAYOUT_US;
  } else {
    // If jumper 1 is HIGH then...
    // return DE layout if jumper 2 is also HIGH
    // otherwise, return FR layout (e.g. jumper 2 is LOW)
    return digitalRead(LK_KB_SETTING_2)
         ? LK_LAYOUT_DE : LK_LAYOUT_FR;
  }
}

static inline uint8_t raw2scan(uint8_t raw) {
    return (raw == M0110_NULL) ?  M0110_NULL : (
                (raw == M0110_ERROR) ?  M0110_ERROR : (
                    ((raw&0x80) | ((raw&0x7F)>>1))
                )
           );
}

void setup(void)
{
  unsigned char fkeyMap;
  
  //Serial.begin(9600);

  matrix_init();
  
	delayMicroseconds(10000);

  lk_start_output(get_layout_setting());
}


void loop(void)
{
	uint8_t buf;
  uint8_t key;
  uint16_t kc;

  
	// read from the keyboard
  key = matrix_scan();

  if(key != 0xFD)   // Check to see if this is a 'null' response
  {  
    //Serial.print("Scan: ["); print_u8(key); Serial.print("]\n");

    const uint8_t k0 = key & 0x7F;
    const uint8_t r0 = key & 0x80;      

    // The keymap will vary between models
    if(keybrd_model == 0x0B)
    {
        //Serial.print("Macintosh Plus Keyboard!\n");
        const uint16_t kc0 = m0110a_keymap[k0];
        kc = kc0;
    }
    else
    {
        //Serial.print("Macintosh 128k/512k Keyboard!\n");
        const uint16_t kc0 = m0110_keymap[k0];
        kc = kc0;
    }
    
    if (r0)
    {
      // Key release
      //Serial.print("Key Released!\n");
      //Serial.print("Key: "); print_u8(kc); Serial.print("\n\n");
      lk_write_macro(kc | LK_RELEASED);
    }
    else
    {
      // Key press
      //Serial.print("Key Pressed!\n");
      //Serial.print("Key: "); print_u8(kc); Serial.print("\n\n");
      lk_write_macro(kc | LK_PRESSED);
    }
  }

  lk_flush();

	delayMicroseconds(3000);
  
}
