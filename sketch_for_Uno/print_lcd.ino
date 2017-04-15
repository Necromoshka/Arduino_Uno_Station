/// This work
/// \file print_lcd.ino
/// \brief main file
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n

void print_lcd()
{
  //-----------------------Год--------------------------
  if (Data.yea != Data_old.yea)
  {
    lcd.setCursor(0, 0);
    lcd.print("   ");
    lcd.setCursor(0, 0);
    if (Data.yea < 10)
    {
      lcd.print("0");
      lcd.print(Data.yea);
    }
    else
    {
      lcd.print(Data.yea);
    }
    Data_old.yea = Data.yea;
    lcd.print("/");
  }
  //--------------------------------------------Месяц--------------------------------
  if (Data.mns != Data_old.mns)
  {
    lcd.setCursor(3, 0);
    lcd.print("   "); //Библиотека как то странно начинает работать если не заполнять место на экране куда будешь писать пробелами
    lcd.setCursor(3, 0);
    if (Data.mns < 10)
    {
      lcd.print("0");
      lcd.print(Data.mns);
    }
    else
    {
      lcd.print(Data.mns);
    }
    Data_old.mns = Data.mns;
    lcd.print("/");
  }
  //-------------------------------------------------День---------------------------------
  if (Data.dd != Data_old.dd)
  {
    lcd.setCursor(6, 0);
    lcd.print("   ");
    lcd.setCursor(6, 0);
    if (Data.dd < 10)
    {
      lcd.print("0");
      lcd.print(Data.dd);
    }
    else
    {
      lcd.print(Data.dd);
    }
    Data_old.dd = Data.dd;
    lcd.printByte(255);
  }
  //-------------------------------------------------Температура--------------------------
  if (Data.temp != Data_old.temp)
  {
    lcd.setCursor(9, 0);
    lcd.print("    ");
    lcd.setCursor(9, 0);
    if (Data.temp < 10.0)
    {
      lcd.print(" ");
      lcd.print(round(Data.temp));
    }
    else
    {
      lcd.print(round(Data.temp));
    }
    Data_old.temp = Data.temp;
    lcd.printByte(0);
    lcd.print("C");
  }
  //----------------------------------------------------Влажность----------------------------
  if (Data.hum != Data_old.hum)
  {
    lcd.setCursor(13, 0);
    lcd.print("   ");
    lcd.setCursor(13, 0);
    if (Data.hum < 10.0)
    {
      lcd.print(" ");
      lcd.print(round(Data.hum));
    }
    else
    {
      lcd.print(round(Data.hum));
    }
    Data_old.hum = Data.hum;
    lcd.print("%");
  }
  //----------------------------------------------Час----------------------------------
  if (Data.hh != Data_old.hh)
  {
    lcd.setCursor(0, 1);
    lcd.print("   ");
    lcd.setCursor(0, 1);
    if (Data.hh < 10)
    {
      lcd.print("0");
      lcd.print(Data.hh);
    }
    else
    {
      lcd.print(Data.hh);
    }
    Data_old.hh = Data.hh;
    lcd.print(":");
  }
  //--------------------------------------Минута----------------------------------
  if (Data.mm != Data_old.mm)
  {
    lcd.setCursor(3, 1);
    lcd.print("   ");
    lcd.setCursor(3, 1);
    if (Data.mm < 10)
    {
      lcd.print("0");
      lcd.print(Data.mm);
    }
    else
    {
      lcd.print(Data.mm);
    }
    Data_old.mm = Data.mm;
    lcd.print(":");
  }
  //-----------------------------------------Секунда----------------------------------
  if (Data.ss != Data_old.ss)
  {
    lcd.setCursor(6, 1);
    lcd.print("  ");
    lcd.setCursor(6, 1);
    if (Data.ss < 10)
    {
      lcd.print("0");
      lcd.print(Data.ss);
    }
    else
    {
      lcd.print(Data.ss);
    }
    Data_old.ss = Data.ss;
    lcd.printByte(255);
  }
  //-----------------------------------------Для Радио-----------------------------------

  //-----------------------------------------Давление------------------------------------
  if (Data.pres != Data_old.pres)
  { 
    lcd.print("   ");
    lcd.setCursor(13, 1);
    lcd.print(((round(Data.pres)*760)/101325)); // расчёт давления 
    Data_old.pres = Data.pres;
  }
}

