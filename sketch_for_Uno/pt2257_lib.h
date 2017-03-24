/// This work
/// \pt2257_lib.h
/// \brief main file
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
  private:
    uint8_t _vol;
    boolean _mut;

};
# endif

/*#include <Wire.h>

  void setup() {
  Wire.begin();
  }

  void loop() {
  Wire.beginTransmission(0x44);  // i2c adress pt2257
  Wire.write(0b11111111);        // задаем десятки
  Wire.write(0b11111111);        // задаем еденицы
  Wire.endTransmission();
  }

  Команды:
  для 2 каналов:
  0b01111000 //MUTE OFF
  0b01111001 //MUTE ON
  0b11111111 //Function OFF (-79dB)

  0b11010000 // -0
  0b11010001 // -1
  0b11010010 // -2
  0b11010011 // -3
  0b11010100 // -4
  0b11010101 // -5
  0b11010110 // -6
  0b11010111 // -7
  0b11011000 // -8
  0b11011001 // -9

  0b11100000 // -00
  0b11100001 // -10
  0b11100010 // -20
  0b11100011 // -30
  0b11100100 // -40
  0b11100101 // -50
  0b11100110 // -60
  0b11100111 // -70

*/

