/// This work
/// \file pt2257_lib.cpp
/// \brief main file
/// \author Klimets Sergey
/// \base on https://github.com/victornpb/Evc_pt2257
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n
/// for Uno or nano
#include "pt2257_lib.h"

void pt2257::set_volium(uint8_t v)
{
  if (v > 79)  v = 79;


  uint8_t dec = v / 10;
  uint8_t ed = v % 10;
  Wire.beginTransmission(Addr);
  Wire.write(dec | pt_10);
  Wire.write(ed | pt_1);
  Wire.endTransmission();
}

void pt2257::set_mute(boolean m)
{
  Wire.beginTransmission(Addr);
  Wire.write(pt_mute | (m & 0b00000001));
  Wire.endTransmission();
}

void pt2257::init()
{
  delay(200);
  Wire.begin();
}

