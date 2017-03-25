/// This work
/// \pt2257_lib.h
/// \brief main file
/// \base on https://github.com/victornpb/Evc_pt2257
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n
/// for Uno or nano
# ifndef ENCODER_H
# define ENCODER_H
# define Addr 0x88
# define pt_off     0b11111111  // -79dB
# define pt_1   0b11010000  // еденицы для 2 - х каналов
# define pt_10  0b11100000  // десятки для 2 - х каналов
# define pt_mute    0b01111000  // MUTE
# include "Arduino.h"
# include "Wire.h"

class pt2257
{
  public:
    pt2257();
    void init();
    void set_volium(uint8_t);
    void set_mute(boolean);
};
# endif

