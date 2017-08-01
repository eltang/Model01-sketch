/* -*- mode: c++ -*-
 * Model01-Sketch -- algernon's Model01 Sketch
 * Copyright (C) 2016, 2017  Gergely Nagy
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
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "00-config.h"
#include "Layers.h"
#include "Leader.h"

#include <Kaleidoscope-Macros.h>
#include <Kaleidoscope-LEDControl.h>
#include <Kaleidoscope-Unicode.h>
#include <Kaleidoscope-Syster.h>
#include <Kaleidoscope-LangPack-Hungarian.h>
#include <Kaleidoscope-OneShot.h>

#include "Macros.h"

namespace algernon {
namespace Leader {

// Leaders
enum {
  LEAD_UNICODE_UCIS,

  LEAD_CSILLA,
  LEAD_KIDS,
  LEAD_GERGO,
  LEAD_SHRUGGY,

  LEAD_LEDEFFECT,

  LEAD_BUTTERFLY,
  LEAD_STENO,
};

static void Shruggy(uint8_t seqIndex) {
  ::Unicode.type(0xaf);
  ::Macros.play(MACRO(Tc(Backslash),
                      D(RightShift),
                      Tc(Minus),
                      Tc(9),
                      U(RightShift),
                      END));
  ::Unicode.type(0x30c4);
  ::Macros.play(MACRO(D(RightShift),
                      Tc(0),
                      Tc(Minus),
                      U(RightShift),
                      Tc(Slash),
                      END));
  ::Unicode.type(0xaf);
}

static void startUCIS(uint8_t seqIndex) {
  handleKeyswitchEvent(SYSTER, 255, 255, IS_PRESSED | INJECTED);
}

static void Kids(uint8_t seqIndex) {
  ::Macros.play(MACRO(Tc(Spacebar), Tr(LSHIFT(Key_7)), Tc(Spacebar), END));
  ::Unicode.type(0x1f476);
  ::Unicode.type(0x1f476);
}

static void NextLEDEffect(uint8_t seqIndex) {
  LEDControl.next_mode();
}

static void Butterfly(uint8_t seqIndex) {
  ::Macros.play(MACRO(I(10),
                      D(LeftAlt), W(100), Tc(X), W(100), U(LeftAlt),
                      W(100), W(100),
                      Tc(B), Tc(U), Tc(T), Tc(T), Tc(E), Tc(R), Tc(F), Tc(L), Tc(Y),
                      W(100), W(100),
                      Tc(Enter), W(100),
                      Tc(Y), END));
}

static void Steno(uint8_t seqIndex) {
  Layer.on(_PLOVER);
}

static const kaleidoscope::Leader::dictionary_t dictionary[] PROGMEM = LEADER_DICT
    ([LEAD_UNICODE_UCIS]   = {LEADER_SEQ(LEAD(MAIN), Key_U), startUCIS},

     [LEAD_CSILLA]          = {LEADER_SEQ(LEAD(MAIN), Key_C), (kaleidoscope::Leader::action_t)algernon::Macros::Csilla},
     [LEAD_KIDS]            = {LEADER_SEQ(LEAD(MAIN), Key_K), Kids},
     [LEAD_GERGO]           = {LEADER_SEQ(LEAD(MAIN), Key_G), (kaleidoscope::Leader::action_t)algernon::Macros::Gergo},
     [LEAD_SHRUGGY]         = {LEADER_SEQ(LEAD(MAIN), Key_S), Shruggy},

     [LEAD_LEDEFFECT]       = {LEADER_SEQ(LEAD(MAIN), LEAD(MAIN)), NextLEDEffect},

     [LEAD_BUTTERFLY]       = {LEADER_SEQ(LEAD(MAIN), OSM(LeftAlt)), Butterfly},
     [LEAD_STENO]           = {LEADER_SEQ(LEAD(MAIN), Key_P), Steno});

void configure(void) {
  Kaleidoscope.use(&::Leader, &::Unicode);

  ::Leader.dictionary = dictionary;
}

}
}
