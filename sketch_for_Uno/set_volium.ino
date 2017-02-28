/// This work
/// \file set_volium.ino
/// \brief main file
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n

void set_volium()
{
  long newPos = myEnc.read();
  int cnt = 0;
  if (newPos != positions)
  {

    // set_volium(newPos);

    if (newPos > positions)
    {
      positions = newPos;
      if (volium != 1 && cnt == 0)
      {
        volium = volium + 1;
        // radio.setVolume(volium);
        cnt++;
      }
      else cnt--;
    }
    if (newPos < positions)
    {
      positions = newPos;
      if (volium != 0 && cnt == 0)
      {
        volium = volium - 1;
        // radio.setVolume(volium);
      }
      else cnt--;
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
      lcd.print("on");
      lcd.setCursor(12, 1);
      lcd.printByte(255);
      //lcd.print(volium);
      radio.setMute(!mute);
    }
    positions = newPos;
  }
  debounce();
}
