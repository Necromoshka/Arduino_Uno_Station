/// This work
/// \file setstation.ino
/// \brief main file
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n

void setstation(int st)
{
  switch (st)
  {
    case 1:
      radio.setFrequency(9240);
      break;
    case 2:
      radio.setFrequency(9280);
      break;
    case 3:
      radio.setFrequency(9350);
      break;
    case 4:
      radio.setFrequency(9390);
      break;
    case 5:
      radio.setFrequency(9470);
      break;
    case 6:
      radio.setFrequency(9560);
      break;
    case 7:
      radio.setFrequency(9600);
      break;
    case 8:
      radio.setFrequency(9640);
      break;
    case 9:
      radio.setFrequency(9680);
      break;
    case 10:
      radio.setFrequency(9760);
      break;
    case 11:
      radio.setFrequency(9800);
      break;
    case 12:
      radio.setFrequency(9860);
      break;
    case 13:
      radio.setFrequency(9910);
      break;
    case 14:
      radio.setFrequency(9950);
      break;
    case 15:
      radio.setFrequency(10000);
      break;
    case 16:
      radio.setFrequency(10040);
      break;
    case 17:
      radio.setFrequency(10090);
      break;
    case 18:
      radio.setFrequency(10140);
      break;
    case 19:
      radio.setFrequency(10190);
      break;
    case 20:
      radio.setFrequency(10240);
      break;
    case 21:
      radio.setFrequency(10290);
      break;
    case 22:
      radio.setFrequency(10340);
      break;
    case 23:
      radio.setFrequency(10370);
      break;
    case 24:
      radio.setFrequency(10390);
      break;
    case 25:
      radio.setFrequency(10450);
      break;
    case 26:
      radio.setFrequency(10490);
      break;
    case 27:
      radio.setFrequency(10540);
      break;
    case 28:
      radio.setFrequency(10590);
      break;
    case 29:
      radio.setFrequency(10640);
      break;
    case 30:
      radio.setFrequency(10690);
      break;
    case 31:
      radio.setFrequency(10740);
      break;
    case 32:
      radio.setFrequency(10790);
      break;
  }
  rtc.eeprom_write(vol_ee, (unsigned char) st);
  debounce();
}

