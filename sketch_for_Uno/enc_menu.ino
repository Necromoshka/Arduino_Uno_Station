/// This work
/// \file enc_menu.ino
/// \brief main file
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n

void enc_menu_v()
{

  bu_fl = true;
  while (bu_fl)
  {

    set_volium();

    debounce();

  }
}

void enc_menu_r()
{

  bu_fl = true;
  while (bu_fl)
  {

    set_station();

    debounce();

  }
}

