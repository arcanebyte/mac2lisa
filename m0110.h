/*
Copyright 2011,2012 Jun WAKO <wakojun@gmail.com>

This software is licensed with a Modified BSD License.
All of this is supposed to be Free Software, Open Source, DFSG-free,
GPL-compatible, and OK to use in both free and proprietary applications.
Additions and corrections to this file are welcome.


Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in
  the documentation and/or other materials provided with the
  distribution.

* Neither the name of the copyright holders nor the names of
  contributors may be used to endorse or promote products derived
  from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

https://raw.githubusercontent.com/tmk/tmk_keyboard/master/tmk_core/protocol/m0110.h
*/

#ifndef M0110_H
#define M0110_H



/* Commands */
#define M0110_INQUIRY       0x10
#define M0110_INSTANT       0x14
#define M0110_MODEL         0x16
#define M0110_TEST          0x36

/* Response(raw byte from M0110) */
#define M0110_NULL          0x7B
#define M0110_KEYPAD        0x79
#define M0110_TEST_ACK      0x7D
#define M0110_TEST_NAK      0x77
#define M0110_SHIFT         0x71
#define M0110_ARROW_UP      0x1B
#define M0110_ARROW_DOWN    0x11
#define M0110_ARROW_LEFT    0x0D
#define M0110_ARROW_RIGHT   0x05

/* Release Code (M0110A) */
//#define M0110A_ARROW_UP_RELEASE

/* This inidcates no response. */
#define M0110_ERROR         0xFF

/* scan code offset for keypad and arrow keys */
#define M0110_KEYPAD_OFFSET 0x40
#define M0110_CALC_OFFSET   0x60


extern uint8_t m0110_error;

/* host role */
void m0110_init(void);
uint8_t m0110_send(uint8_t data);
uint8_t m0110_model_query(void);
uint8_t m0110_recv(void);
uint8_t m0110_recv_key(void);
uint8_t m0110_inquiry(void);
uint8_t m0110_instant(void);


#endif
