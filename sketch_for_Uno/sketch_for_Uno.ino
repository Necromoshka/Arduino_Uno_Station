/**
  #include "uRTCLib.h"
   @copyright Naguissa
   @author Naguissa
   @email naguissa.com@gmail.com
   @version 1.0
   @created 2015-05-07

   #include "LiquidCrystal_I2C.h"
  YWROBOT
  Compatible with the Arduino IDE 1.0
  Library version:1.1

  BME280I2C.h
  This code records data from the BME280 sensor and provides an API.
  This file is part of the Arduino BME280 library.
  Copyright (C) 2016  Tyler Glenn

   file Radio.h
   brief Library header file for the radio libraries to control radio chips.
   author Matthias Hertel, http://www.mathertel.de
   copyright Copyright (c) 2014 by Matthias Hertel.
*/
/// This work
/// \file sketch_for_Uno.ino
/// \brief main file
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n
/// \git Branch master



//-----------------------Include--------------------------------------------------
#include "Arduino.h"
#include "Wire.h"
#include "uRTCLib.h"
#include "LiquidCrystal_I2C.h"
#include "BME280I2C.h"
#include "radio.h"
#include "TEA5767.h"
#include "encoder_lib.h"
#include "pt2257_lib.h"

//-----------------------End Include----------------------------------------------

//-----------------------Define----------------------------------------------------
#define pin_A 2 //Pin A Encoder
#define pin_B 3 //Pin B Encoder
#define pin_C 4 //Pin Button
#define metric true //metric? для BME280
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args); //Для LCD
#else
#define printByte(args)  print(args,BYTE);
#endif
#define FIX_BAND RADIO_BAND_FM //Выбираем диапазон для радио (есть разные варианты)
#define FIX_STATION 9350 //Частота Нашего радио в ННовгороде. Радиостанция которая ставится по умолчанию(Можно 
// заменить на что-то из EEPROM например на последнюю выбраную.
#define i2c_lcd_address 0x27 //Адрес экрана
#define coll 16 //Кол-во столбцов
#define row 2 //Кол-во строк
#define st_ee 0 //позиция в памяти станции
#define vol_ee 1 //позиция в памяти станции
#define alt 2 //относительная корректировка давления

//------------------------End Define-----------------------------------------------

//------------------------Var------------------------------------------------------
uRTCLib rtc; //Часы
BME280I2C bme; //Датчик погоды
LiquidCrystal_I2C lcd(i2c_lcd_address, coll, row);//Экран
TEA5767 radio;//Радио чип TEA
Encoder enc(pin_A, pin_B); //Энкодер
pt2257 dpow; //Регулятор громкости


volatile boolean flag = true; //flag для часов
volatile boolean flag2 = true; //flag2 для датчика погоды
volatile boolean bu_fl = true; //bu_fl для кнопки на энкодере
long positions  = 0;//----------------------------------------------------------------???????????????????
uint8_t volium = 0; //Начальный уровень громкости при 1 -м заходе в меню
unsigned int station = 1; //Начальная станция при 1 - м заходе в меню
boolean mute = true; //Вкл выкл звук на TEA

struct data //Все считываемые данные (BME + DS)
{
  float temp;
  float hum;
  float pres;
  short yea;
  short mns;
  short dd;
  short hh;
  short mm;
  short ss;
};
data Data, Data_old; // 2 переменные нужно для сравнения данных старых и новых.

uint8_t cels[8]  = { // знак цельсия кружочек
  B00010,
  B00101,
  B00010,
  B00000,
  B00000,
  B00000,
  B00000,
};
uint8_t men = 0; // Позиция в меню
uint16_t update_time_rtc = 1000; // время обнавления часов
uint16_t update_time_bme = 5000; // время обнавления датчика погоды
unsigned long time_millis_rtc; // Время отсчитываемое для обновления часов
unsigned long time_millis_bme; // Время отсчитываемое для обновления датчика погоды
boolean buttonState;             // Текущее состояние кнопки
boolean  lastButtonState = HIGH;   // Предидущие состояние кнопки
unsigned long lastDebounceTime = 0;  // Время с момента последнего нажатия
unsigned long debounceDelay = 50;    // время необходимое для устранения дребезга (можно увеличить если плохо работает)

//------------------------End Var--------------------------------------------------


void setup() {
 // Serial.begin(9600);
  // rtc.set_ee_address(0x57);
  // Only used once, then disabled
  // rtc.set(0, 54, 20, 5, 14, 4, 17);
  //  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
  dpow.init();
  lcd.init();
  lcd.backlight();

  lcd.createChar(0, cels);
  lcd.home();

  //pinMode(pin_A, INPUT);  //pin_B
  pinMode(pin_C, INPUT);  //pin_C Button on encoder
  // pinMode (pin_B, INPUT); //pin_B
  digitalWrite(pin_C, HIGH); //Подтягиваем кнопку к +5В

  while (!bme.begin()) //Ждём включение датчика (Если нет то сообщаем об этом)
  {
    lcd.clear();
    lcd.print("Could not find" );
    lcd.setCursor(0, 1);
    lcd.print("BME280 sensor!");
    delay(1000);
  }
  ///////////////////////////////////// Пишем на экране, что радио включено.
  lcd.setCursor(9, 1);
  lcd.print("on");
  lcd.setCursor(12, 1);
  lcd.printByte(255);
  /////////////////////////////
  // myEnc.write(0);

  radio.init(); // Включаем чип
  //  station = (int) rtc.eeprom_read(st_ee);
  if (station < 1) station = 1;
  if (station > 32) station = 32;
  radio.setBandFrequency(FIX_BAND, station); // Устанавливаем частотный диаппазон и частоту
  // volium = (int) rtc.eeprom_read(vol_ee);
  if (volium <= 0)
  {
    volium = 0;
    //radio.setMono(mute); // включаем звук
  }
  if (volium > 79) volium = 79;
  if (volium > 0 || volium <= 79)
  {
    volium = 79;
    dpow.set_volium(volium);
    radio.setMute(!mute);
  }
  //radio.setMono(mute); // включаем звук



  attachInterrupt(0, int0, CHANGE);
  attachInterrupt(1, int1, CHANGE);
}

void loop() {

  if (flag)
  {
    time_millis_rtc = millis(); // Время прошедшее с момента старта
    flag = false;
  }

  if (flag2)
  {
    time_millis_bme = millis(); // Время прошедшее с момента старта
    flag2 = false;
  }

  read_data(); //Считывание данных с датчика
  print_lcd(); //Печатаем данные, но только новые,если данные не изменились не ечатаем
  debounce(); //Проверяем не нажата ли кнопка
  read_button(); //Функция обработки нажатия кнопки

}
