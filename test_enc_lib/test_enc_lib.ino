#include "Arduino.h"
#include "encoder_lib.h"
#define pin_A 2 //Pin A Encoder
#define pin_B 3 //Pin B Encoder
Encoder enc(pin_A, pin_B);
void setup() {
  Serial.begin(9600);
  Serial.println("START");
  attachInterrupt(0, int0, CHANGE);
  attachInterrupt(1, int1, CHANGE);
}
long actualRotaryTicks;
void loop() {
  if (actualRotaryTicks != enc.get_position())
  {
    Serial.println(actualRotaryTicks);
    actualRotaryTicks = enc.get_position();
  }
}

void int0()
{
  enc.int0();
}

void int1()
{
  enc.int1();
}

