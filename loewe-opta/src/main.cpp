#include <Arduino.h>

#include "switch_debounce_helper.h"

#define SMALL_BUTTON 4
#define BIG_BUTTON 2

uint16_t delay_local{100};

SwitchDebounceHelper SwitchBig_obj(BIG_BUTTON);
SwitchDebounceHelper SwitchSmall_obj(SMALL_BUTTON);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (SwitchSmall_obj.SwitchPressed())
  {
    if (delay_local <= 900)
    {
      delay_local = delay_local + 100;
    }
  } else if (SwitchBig_obj.SwitchPressed())
  {
    if (delay_local >= 100)
    {
      delay_local = delay_local - 100;
    }
  }

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(delay_local);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(delay_local);
}