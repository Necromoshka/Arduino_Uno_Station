/// This work
/// \file debounce.ino
/// \brief main file
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n

void debounce()
{
  bool reading = digitalRead(pin_C); //читаем состояние кнопки
  if (reading != lastButtonState) // сравниваем с предыдущим
  {
    lastDebounceTime = millis(); //время нажатия кнопки
  }
  if ((millis() - lastDebounceTime) > debounceDelay) //сравниваем время прошедшее с момента нажатия с временем задержки
  {
    if (reading != buttonState) 
    {
      buttonState = reading;
      if (buttonState == LOW)
      {
        bu_fl = false; // Флаг сигнализирует о том, что кнопка была нажата. 
      }
    }
  }
  lastButtonState = reading;
}

