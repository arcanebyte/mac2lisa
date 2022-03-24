/*
 * lisakeys.cpp
 * 
 * Copyright 2018 - Rebecca Bettencourt
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

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lisakeyslib.h"


#define LK_PACKET_IN_SYNC  20
#define LK_PACKET_IN_START 23
#define LK_PACKET_IN_SHORT 15
#define LK_PACKET_IN_LONG1 23
#define LK_PACKET_IN_LONG2 23
#define LK_PACKET_IN_STOP  24

#define LK_PACKET_IN_MAX_DELAY  128
#define LK_PACKET_IN_MIN_PERIOD 768


static unsigned char layoutID;
static unsigned char keyBuffer[LK_BUFFER_SIZE];
static unsigned char keyBufStart;
static unsigned char keyBufEnd;

void lk_soft_power() {
    keyBuffer[0] = LK_INIT;
    keyBuffer[1] = LK_SOFTPOWER;
    keyBufStart = 0;
    keyBufEnd = 2;
    return;
}

void lk_start_output(unsigned char layout) {
  LK_DDR  &=~ LK_MASK; // input
  LK_PORT |=  LK_MASK; // pull up
  layoutID = layout;
  keyBuffer[0] = LK_INIT;
  keyBuffer[1] = layout;
  keyBufStart = 0;
  keyBufEnd = 2;
}

void lk_write(unsigned char packet) {
  keyBuffer[keyBufEnd] = packet;
  keyBufEnd++;
  keyBufEnd &= (LK_BUFFER_SIZE - 1);
  if (keyBufEnd == keyBufStart) {
    // Buffer overflowed. Ignore input.
    keyBufEnd--;
    keyBufEnd &= (LK_BUFFER_SIZE - 1);
  }
}

void lk_write_macro(unsigned int packet) {
  
  if (packet & 0x80) {
    // Key is pressed
    if (packet & LK_MACRO_APPLE) {
      lk_write(LK_APPLE | LK_PRESSED);
      lk_delay(LK_WRITE_DELAY);
    }
    if (packet & LK_MACRO_LTOPT) {
      lk_write(LK_LT_OPTION | LK_PRESSED);
      lk_delay(LK_WRITE_DELAY);
    }
    if (packet & LK_MACRO_RTOPT) {
      lk_write(LK_RT_OPTION | LK_PRESSED);
      lk_delay(LK_WRITE_DELAY);
    }
    if (packet & LK_MACRO_SHIFT) {
      lk_write(LK_SHIFT | LK_PRESSED);
      lk_delay(LK_WRITE_DELAY);
    }
  }
  
  lk_write(packet & 0xFF);
  
  if (!(packet & 0x80)) {
    // Key is released
    if (packet & LK_MACRO_SHIFT) {
      lk_delay(LK_WRITE_DELAY);
      lk_write(LK_SHIFT | LK_RELEASED);
    }
    if (packet & LK_MACRO_RTOPT) {
      lk_delay(LK_WRITE_DELAY);
      lk_write(LK_RT_OPTION | LK_RELEASED);
    }
    if (packet & LK_MACRO_LTOPT) {
      lk_delay(LK_WRITE_DELAY);
      lk_write(LK_LT_OPTION | LK_RELEASED);
    }
    if (packet & LK_MACRO_APPLE) {
      lk_delay(LK_WRITE_DELAY);
      lk_write(LK_APPLE | LK_RELEASED);
    }
  }
}


void lk_delay(unsigned long ms) {
  unsigned long time = millis();
  while ((millis() - time) < ms) {
    lk_flush();
  }
}

// Nominally 12?, 16, 16, 32, 16, but have to be adjusted
// to compensate for time taken by the microcontroller.
// These have been adjusted to work with a real Lisa.
#define LK_PACKET_OUT_DELAY 10
#define LK_PACKET_OUT_START 15
#define LK_PACKET_OUT_SHORT 15
#define LK_PACKET_OUT_LONG  30
#define LK_PACKET_OUT_STOP  15

//#define LK_PACKET_OUT_DELAY 12
//#define LK_PACKET_OUT_START 16
//#define LK_PACKET_OUT_SHORT 16
//#define LK_PACKET_OUT_LONG  32
//#define LK_PACKET_OUT_STOP  16

void lk_flush() {
  
  // Wait for start of sync signal.
  unsigned long time = micros();
  while (LK_INPUT & LK_MASK) {
    if ((micros() - time) > 4096) {
      // If start of sync doesn't come, try later.
      return;
    }
  }

  // Wait for end of sync signal.
  time = micros();
  while (!(LK_INPUT & LK_MASK));
  if ((micros() - time) > 128) {
    // If too long to be a sync signal, reset.
    keyBuffer[0] = LK_INIT;
    keyBuffer[1] = layoutID;
    keyBufStart = 0;
    keyBufEnd = 2;
    return;
  }

  // If no output, don't respond.
  if (keyBufStart == keyBufEnd) {
    return;
  }

  noInterrupts();

  // Write data packet.
  unsigned char packet = keyBuffer[keyBufStart];
  keyBufStart++;
  keyBufStart &= (LK_BUFFER_SIZE - 1);
  _delay_us(LK_PACKET_OUT_DELAY);

  // start bit
  // Drive low
  LK_DDR  |=  LK_MASK; // output
  LK_PORT &=~ LK_MASK; // pull down
  _delay_us(LK_PACKET_OUT_START);

  // bit 4
  if (packet & 0x10) LK_PORT &=~ LK_MASK; // pull down
  else               LK_PORT |= LK_MASK; // pull up
  _delay_us(LK_PACKET_OUT_SHORT);

  // bit 5
  if (packet & 0x20) LK_PORT &=~ LK_MASK; // pull down
  else               LK_PORT |= LK_MASK; // pull up
  _delay_us(LK_PACKET_OUT_SHORT);

  // bit 6
  if (packet & 0x40) LK_PORT &=~ LK_MASK; // pull down
  else               LK_PORT |= LK_MASK; // pull up
  _delay_us(LK_PACKET_OUT_SHORT);

  // bit 7
  if (packet & 0x80) LK_PORT &=~ LK_MASK; // pull down
  else               LK_PORT |= LK_MASK; // pull up
  _delay_us(LK_PACKET_OUT_LONG);

  // bit 0
  if (packet & 0x01) LK_PORT &=~ LK_MASK; // pull down
  else               LK_PORT |= LK_MASK; // pull up
  _delay_us(LK_PACKET_OUT_SHORT);

  // bit 1
  if (packet & 0x02) LK_PORT &=~ LK_MASK; // pull down
  else               LK_PORT |= LK_MASK; // pull up
  _delay_us(LK_PACKET_OUT_SHORT);

  // bit 2
  if (packet & 0x04) LK_PORT &=~ LK_MASK; // pull down
  else               LK_PORT |= LK_MASK; // pull up
  _delay_us(LK_PACKET_OUT_SHORT);

  // bit 3
  if (packet & 0x08) LK_PORT &=~ LK_MASK; // pull down
  else               LK_PORT |= LK_MASK; // pull up
  _delay_us(LK_PACKET_OUT_SHORT);

  // stop bit
  LK_DDR  &=~ LK_MASK; // input
  LK_PORT |=  LK_MASK; // pull up
  _delay_us(LK_PACKET_OUT_STOP);

  interrupts(); // Re-enable interrupts

}

static const unsigned int PROGMEM fkeysMac[] = {
  (LK_MACRO_APPLE | LK_MACRO_SHIFT | LK_1         ),
  (LK_MACRO_APPLE | LK_MACRO_SHIFT | LK_2         ),
  (LK_MACRO_APPLE | LK_MACRO_SHIFT | LK_3         ),
  (LK_MACRO_APPLE | LK_MACRO_SHIFT | LK_4         ),
  (LK_MACRO_APPLE | LK_MACRO_SHIFT | LK_5         ),
  (LK_MACRO_APPLE | LK_MACRO_SHIFT | LK_6         ),
  (LK_MACRO_APPLE | LK_MACRO_SHIFT | LK_7         ),
  (LK_MACRO_APPLE | LK_MACRO_SHIFT | LK_8         ),
  (LK_MACRO_APPLE | LK_MACRO_SHIFT | LK_9         ),
  (LK_MACRO_APPLE | LK_MACRO_SHIFT | LK_0         ),
  (LK_MACRO_APPLE | LK_MACRO_SHIFT | LK_MINUS     ),
  (LK_MACRO_APPLE | LK_MACRO_SHIFT | LK_EQUAL     ),
  (LK_MACRO_APPLE | LK_MACRO_SHIFT | LK_LT_BRACKET),
  (LK_MACRO_APPLE | LK_MACRO_SHIFT | LK_RT_BRACKET),
  (LK_MACRO_APPLE | LK_MACRO_SHIFT | LK_BACKSLASH ),
};

static const unsigned int PROGMEM fkeysZXCV[] = {
  (LK_MACRO_APPLE | LK_Z), // Undo
  (LK_MACRO_APPLE | LK_X), // Cut
  (LK_MACRO_APPLE | LK_C), // Copy
  (LK_MACRO_APPLE | LK_V), // Paste
  (LK_MACRO_APPLE | LK_N), // New
  (LK_MACRO_APPLE | LK_O), // Open
  (LK_MACRO_APPLE | LK_S), // Save
  (LK_MACRO_APPLE | LK_P), // Print
  (LK_MACRO_APPLE | LK_T), // Text Style
  (LK_MACRO_APPLE | LK_B), // Bold
  (LK_MACRO_APPLE | LK_I), // Italic
  (LK_MACRO_APPLE | LK_U), // Underline
  (LK_MACRO_APPLE | LK_F),
  (LK_MACRO_APPLE | LK_G),
  (LK_MACRO_APPLE | LK_H),
};
