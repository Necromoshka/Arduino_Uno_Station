/// This work
/// \file set_station.ino
/// \brief main file
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n

void set_station()
{
  long newPos = enc.get_position(); //myEnc.read();
 // int cnt = 0;
  if (newPos != positions)
  {
    if (newPos > positions)
    {
      positions = newPos;
      if (station != 32)
      {
        station++;  
      }
    }
    if (newPos < positions)
    {
      positions = newPos;
      if (station != 1)
      {
        station--;
      }
    }
    positions = newPos;
    lcd.setCursor(9, 1);
    lcd.print("   ");
    lcd.setCursor(9, 1);
    lcd.print("R");
    lcd.print(station);
    if (station < 10)
    {
      lcd.printByte(255);
    }
    else
    {
      lcd.setCursor(12, 1);
      lcd.printByte(255);
    }
  }
  debounce();

}
