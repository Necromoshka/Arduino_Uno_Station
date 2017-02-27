/// This work
/// \file debounce.ino
/// \brief main file
/// \author Klimets Sergey
/// \copyright Copyright (c) 2017 by Klimets Sergey.\n

void debounce()
{
  bool reading = digitalRead(pin_C);
  if (reading != lastButtonState)
  {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (reading != buttonState)
    {
      buttonState = reading;
      if (buttonState == LOW)
      {
        bu_fl = false;
      }
    }
  }
  lastButtonState = reading;
}

