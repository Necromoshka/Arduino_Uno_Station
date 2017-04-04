/// This work
/// \file read_button.ino
/// \brief main file
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n

void read_button()
{ 
  
  while (bu_fl)
  {
    if (!bu_fl)
    {
      switch (men)
      {
        case 0:
          enc.set_position(0);
          enc_menu_v();
          bu_fl = true;
          men++;

          break;
        case 1:
          enc.set_position(0);
          enc_menu_r();
          bu_fl = true;
          men++;
          setstation(station);

          break;

        case 2:
          enc_settings();
          bu_fl = true;
          men++;
          break;

        case 3:
          bu_fl = true;
          bu_fl =  enc_exit();
          men = 0;
          break;

      }
    }
  }

}
