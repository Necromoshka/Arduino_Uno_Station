/// This work
/// \file read_data.ino
/// \brief main file
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n

void read_data()

{
  if (millis() > (time_millis_bme + update_time_bme))
  {
    bme.read(Data.pres, Data.temp, Data.hum, metric);
    flag2 = true;
  }
  if (millis() > (time_millis_rtc + update_time_rtc))
  {
    rtc.refresh();
    flag = true;
    Data.yea = rtc.year();
    Data.mns = rtc.month();
    Data.dd = rtc.day();
    Data.hh = rtc.hour();
    Data.mm = rtc.minute();
    Data.ss = rtc.second();
  }
}
