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
//#include "SPI.h"
//#include "Ethernet.h"
//-----------------------End Include----------------------------------------------

//-----------------------Define----------------------------------------------------
#define pin_A 3
#define pin_B 2
#define pin_C 4
//#define sq_signal 0
//#define but_int 1
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

//byte mac[] = {
//  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
//};
//IPAddress ip(192, 168, 52, 20);
//EthernetServer server(80);

volatile bool flag = true; //flag int 1
volatile bool flag2 = true; //flag int 1
volatile bool bu_fl = true; //flag int 2
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
uint16_t update_time_rtc = 1000;
uint16_t update_time_bme = 5000;
unsigned long time_millis_rtc;
unsigned long time_millis_bme;
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

//------------------------End Var--------------------------------------------------


void setup() {
  // Only used once, then disabled
    //rtc.set(0, 47, 21, 1, 27, 2, 17);
  //  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
 // Serial.begin(9600);
 // while (!Serial) ;
 // Ethernet.begin(mac, ip);
 // Serial.print("server is at ");
 // Serial.println(Ethernet.localIP());

  lcd.init();
  lcd.backlight();

  lcd.createChar(0, cels);
  lcd.home();

  pinMode(2, INPUT); //int
  pinMode(pin_C, INPUT); //int
  pinMode (pin_A, INPUT);
  pinMode (pin_B, INPUT);
  //pinMode(pin_C, INPUT_PULLUP);
  digitalWrite(pin_C, HIGH);
  while (!bme.begin()) {
    lcd.clear();
    lcd.print("Could not find" );
    lcd.setCursor(0, 1);
    lcd.print("BME280 sensor!");
    delay(1000);
  }

  //attachInterrupt(sq_signal, refresh, RISING);
  //attachInterrupt(but_int, but_press, FALLING);
  lcd.setCursor(9, 1);
  lcd.print("on");
  lcd.setCursor(12, 1);
  lcd.printByte(255);
  myEnc.write(0);
  radio.init();
  radio.setBandFrequency(FIX_BAND, FIX_STATION);
  //radio.setVolume(2);
  radio.setMono(true);
}

void loop() {
 /* EthernetClient client = server.available();
  if (client)
  {
    Serial.println("new client");
    boolean currentLineIsBlank = true;
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank)
        {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          for (int analogChannel = 0; analogChannel < 6; analogChannel++)
          {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n')
        {
          currentLineIsBlank = true;
        }
        else if (c != '\r')
        {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println("client disconnected");
  }
  */

  
  // while(flag);
  if (flag) {
    time_millis_rtc = millis();
    flag = false;
  }
  if (flag2) {
    time_millis_bme = millis();
    flag2 = false;
  }
  read_data();
  print_lcd();
  debounce();
  read_button();
  //flag = true;
}
