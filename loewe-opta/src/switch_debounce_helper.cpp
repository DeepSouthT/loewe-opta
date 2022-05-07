/*******************************
 * switch_debounce_helper.cpp
 *
 * Created: 07.05.2022 19:01:00
 * Author : DeepSouthT
 *
 * Used:
 *    n/a
 * 
 * Description:
 *     Helper functions for switch debouncing in Arduino projects
 *
 * Last modified: 07.05.2022
 *******************************/

#include "switch_debounce_helper.h"

bool SwitchDebounceHelper::SwitchPressed(void)
{
    uint8_t value = digitalRead(SwitchDebounceHelper::switchPin);
    if (value != SwitchDebounceHelper::previousButtonState) {
    // reset the debouncing timer
    SwitchDebounceHelper::previousDebounceTime = millis();
    SwitchDebounceHelper::previousButtonState = value;
  }

  if ((millis() - SwitchDebounceHelper::previousButtonState) > SwitchDebounceHelper::debounceDelayTime)
  {
    if (value != SwitchDebounceHelper::buttonState)
    {
      SwitchDebounceHelper::buttonState = value;

      if (SwitchDebounceHelper::buttonState == HIGH)
      {
        return true;
      }
    }
  }

  return false;
};