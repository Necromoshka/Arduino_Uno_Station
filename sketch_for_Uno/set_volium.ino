/// This work
/// \file set_volium.ino
/// \brief main file
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n

void set_volium()
{
  long newPos = enc.get_position(); //myEnc.read();
  int cnt = 0;
  if (newPos != positions)
  {

    

    if (newPos > positions)
    {
      positions = newPos;
      if (volium != 1 && cnt == 0)
      {
        volium = volium + 1;

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
