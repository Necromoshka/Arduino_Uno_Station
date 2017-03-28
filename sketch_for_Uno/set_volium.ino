/// This work
/// \file set_volium.ino
/// \brief main file
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n

void set_volium()
{
  long newPos = enc.get_position(); //myEnc.read();
  if (newPos != positions)
  {
    if (newPos > positions)
    {
      positions = newPos;
      if (volium != 79)
      {
        volium = volium + 1;
      }
    }
    if (newPos < positions)
    {
      positions = newPos;
      if (volium != 0)
      {
        volium = volium - 1;

      }
    }
    if (volium == 0)
    {
      lcd.setCursor(9, 1);
      lcd.print("   ");
      lcd.setCursor(9, 1);
      lcd.print("Off");
      lcd.printByte(255);
      radio.setMute(mute);

    }
    else
    {
      lcd.setCursor(9, 1);
      lcd.print("   ");
      lcd.setCursor(9, 1);
      //lcd.print("on");
      lcd.print(volium);
      lcd.setCursor(12, 1);
      lcd.printByte(255);
      //lcd.print(volium);

      dpow.set_volium(volium);
      rtc.eeprom_write(st_ee, (unsigned char) volium);
      radio.setMute(!mute);
    }
    positions = newPos;
  }
  debounce();
}
