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

  #include "Encoder.h"
   Encoder Library, for measuring quadrature encoded signals
   http://www.pjrc.com/teensy/td_libs_Encoder.html
   Copyright (c) 2011,2013 PJRC.COM, LLC - Paul Stoffregen <paul@pjrc.com>

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
//#define ENCODER_DO_NOT_USE_INTERRUPTS
#include "Encoder.h"
#include "radio.h"
#include "TEA5767.h"
//-----------------------End Include----------------------------------------------

//-----------------------Define----------------------------------------------------
#define pin_A 3
#define pin_B 2
#define pin_C 4
#define metric true
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif
#define FIX_BAND RADIO_BAND_FM
#define FIX_STATION 9350
//------------------------End Define-----------------------------------------------

//------------------------Var------------------------------------------------------
Encoder myEnc(pin_A, pin_B);
uRTCLib rtc;
BME280I2C bme;
LiquidCrystal_I2C lcd(0x27, 16, 2);
TEA5767 radio;



volatile bool flag = true; //flag для часов
volatile bool flag2 = true; //flag2 для датчика погоды
volatile bool bu_fl = true; //bu_fl для кнопки на энкодере
long positions  = 0;
int volium = 0;
int station = 1;
bool mute = true;

struct data
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
data Data, Data_old;

uint8_t cels[8]  = {
  B00010,
  B00101,
  B00010,
  B00000,
  B00000,
  B00000,
  B00000,
};
uint8_t men = 0;
bool bl = true;
uint16_t update_time_rtc = 1000; // время обнавления часов
uint16_t update_time_bme = 5000; // время обнавления датчика погоды
unsigned long time_millis_rtc;
unsigned long time_millis_bme;
int buttonState;             // Текущее состояние кнопки
int lastButtonState = HIGH;   // Предидущие состояние кнопки
unsigned long lastDebounceTime = 0;  // Время с момента последнего нажатия
unsigned long debounceDelay = 50;    // время необходимое для устранения дребезга (можно увеличить если плохо работает)

//------------------------End Var--------------------------------------------------


void setup() {
  // Only used once, then disabled
  //rtc.set(0, 47, 21, 1, 27, 2, 17);
  //  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)

  lcd.init();
  lcd.backlight();

  lcd.createChar(0, cels);
  lcd.home();

  pinMode(pin_A, INPUT);  //pin_B
  pinMode(pin_C, INPUT);  //pin_C Button on encoder
  pinMode (pin_B, INPUT); //pin_B
  //pinMode(pin_C, INPUT_PULLUP);
  digitalWrite(pin_C, HIGH);

  while (!bme.begin())
  {
    lcd.clear();
    lcd.print("Could not find" );
    lcd.setCursor(0, 1);
    lcd.print("BME280 sensor!");
    delay(1000);
  }

  lcd.setCursor(9, 1);
  lcd.print("on");
  lcd.setCursor(12, 1);
  lcd.printByte(255);

  myEnc.write(0);

  radio.init();
  radio.setBandFrequency(FIX_BAND, FIX_STATION);
  radio.setMono(true);
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

  read_data();
  print_lcd();
  debounce();
  read_button();

}
