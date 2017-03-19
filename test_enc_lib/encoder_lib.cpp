/// This work
/// \file encoder_lib.cpp
/// \brief main file
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n
/// \base on http://playground.arduino.cc/Main/RotaryEncoders
/// \base on https://www.pjrc.com/teensy/td_libs_Encoder.html#optimize
/// for Uno or nano
#include "encoder_lib.h"

Encoder::Encoder(uint8_t PinA, uint8_t PinB): _pin_a ( PinA), _pin_b( PinB )
{
  digitalWrite(_pin_a, HIGH);
  digitalWrite(_pin_b, HIGH);
  _rotaryHalfSteps = 0;
  _int0time = 0;
  _int1time = 0;
  _int0signal = 0;
  _int1signal = 0;
  _int0history = 0;
  _int1history = 0;

}

long Encoder::get_position()
{
  return (_rotaryHalfSteps / 2);
}

void Encoder::set_position(long pos)
{
  _rotaryHalfSteps = pos;
}

void Encoder::int0()
{
  if ( micros() - _int0time < _threshold )
    return;
  _int0history = _int0signal;
  _int0signal = bitRead(PIND, _pin_a);
  if ( _int0history == _int0signal )
    return;
  _int0time = micros();
  if ( _int0signal == _int1signal )
    _rotaryHalfSteps++;
  else
    _rotaryHalfSteps--;
}

void Encoder::int1()
{
  if ( micros() - _int1time < _threshold )
    return;
  _int1history = _int1signal;
  _int1signal = bitRead(PIND, _pin_b);
  if ( _int1history == _int1signal )
    return;
  _int1time = micros();
}

