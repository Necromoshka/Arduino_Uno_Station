/// This work
/// \file encoder_lib.h
/// \brief main file
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n
/// \base on http://playground.arduino.cc/Main/RotaryEncoders
/// \base on https://www.pjrc.com/teensy/td_libs_Encoder.html#optimize
/// for Uno or nano
#include "Arduino.h"
#ifndef ENCODER_H
#define ENCODER_H
class Encoder
{
  public:

    Encoder(uint8_t PinA, uint8_t PinB);
    long get_position(); //Позиция энкодера
    void set_position(long); //Установить переменную position
    void int0();
    void int1();

  private:

    uint8_t _pin_a;
    uint8_t _pin_b;
    volatile unsigned long _threshold;
    volatile long _rotaryHalfSteps;
    volatile unsigned long _int0time;
    volatile unsigned long _int1time;
    volatile uint8_t _int0signal;
    volatile uint8_t _int1signal;
    volatile uint8_t _int0history;
    volatile uint8_t _int1history;

};
#endif
