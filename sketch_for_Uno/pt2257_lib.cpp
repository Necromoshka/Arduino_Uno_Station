/// This work
/// \file pt2257_lib.cpp
/// \brief main file
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n
/// for Uno or nano
#include "pt2257_lib.h"

/*

       pt2257();
    void set_volium(uint8_t);
    void set_mute(boolean);
  private:
    uint8_t _vol;
    boolean _mut;
*/

pt2257::pt2257()
{
  _vol = 0;
  _mut = true;
}

void pt2257::set_volium(uint8_t v)
{
  if (v > 79)  v = 79;
  if (v < 0)  v = 0;

  uint8_t dec = v / 10;
  uint8_t ed = v % 10;
  Wire.beginTransmission(Addr);
  Wire.write(dec | pt_10); 
  Wire.write(dec | pt_1); 
  Wire.endTransmission();  
}

void pt2257::set_mute(boolean m)
{

}

void pt2257::init()
{
  delay(200);
  
  Wire.begin();
}


/*




  void evc_setVolume(uint8_t dB){
    byte bbbaaaa = evc_level(dB);

    byte aaaa = bbbaaaa & 0b00001111;
    byte bbb = (bbbaaaa>>4) & 0b00001111;

    if (i2c_start(PT2257_ADDR | I2C_WRITE)){
        i2c_write(EVC_2CH_10 | bbb);
        i2c_write(EVC_2CH_1 | aaaa);
        i2c_stop();
    }
  }





  void evc_mute(bool toggle){
    if (i2c_start(PT2257_ADDR | I2C_WRITE)){
        i2c_write(EVC_MUTE | (toggle & 0b00000001));
        i2c_stop();
    }
  }

  void evc_off(){
    if (i2c_start(PT2257_ADDR | I2C_WRITE)){
        i2c_write(EVC_OFF);
        i2c_stop();
    }
  }
*/
* /
