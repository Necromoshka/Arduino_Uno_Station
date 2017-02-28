/// This work
/// \file read_button.ino
/// \brief main file
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n

void read_button()
{
  if (!bu_fl)
  {
    switch (men)
    {
      case 0:
        myEnc.write(0);
        enc_menu_v();
        bu_fl = true;
        men++;

        break;
      case 1:
        myEnc.write(0);
        enc_menu_r();
        bu_fl = true;
        men = 0;
        setstation(station);

        break;
        // case 2:
        //     bl = !bl;
        //      lcd.setBacklight(bl);
        //       men = 0;
        //       bu_fl = true;
        //        break;
    }
  }
}

