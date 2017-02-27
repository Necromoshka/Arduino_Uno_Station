/// This work
/// \file enc_menu.ino
/// \brief main file
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n

void enc_menu_v()
{
  //  bool f = true;
  bu_fl = true;
  while (bu_fl)
  {
    //   long newPos = myEnc.read();
    //  if (newPos != positions)
    //{

    set_volium();
    //   positions = newPos;
    // }
    // myEnc.write(0);
    debounce();
    //   if (!bu_fl)
    //   {
    //    bu_fl = true;
    //    f = false;
    // }
  }
}

void enc_menu_r()
{
  //  bool f = true;
  bu_fl = true;
  while (bu_fl)
  {
    // long newPos = myEnc.read();
    // if (newPos != positions)
    // {

    set_station();
    // positions = newPos;
    // }
    // myEnc.write(0);
    debounce();
    //   if (!bu_fl)
    //   {
    //      bu_fl = true;
    //    f = false;
    //    }
  }
}
//lcd.setCursor(9,1);
//lcd.print("Off");
//lcd.printByte(255);
/*
   void check_encoder()
  {

  long newPos = myEnc.read();
  if (newPos != positions)
  {
   set_volium(newPos);
  }

  }
*/
