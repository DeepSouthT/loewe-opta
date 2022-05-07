/*******************************
 * switch_debounce_helper.h
 *
 * Created: 07.05.2022 18:50:00
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
 
#ifndef __SWITCHDEBOUNCEHELPER_H__
#define __SWITCHDEBOUNCEHELPER_H__

#include <stdint.h>
#include <Arduino.h>
 
class SwitchDebounceHelper
{

public:
	SwitchDebounceHelper( uint8_t pin)
    {
        switchPin = pin;
        pinMode(switchPin, INPUT);
    };
	
    bool SwitchPressed(void);

private:
    uint8_t switchPin = 0;
	uint8_t previousButtonState = 0;
    uint8_t buttonState = 0;
    uint16_t previousDebounceTime = 0;
    const uint16_t debounceDelayTime = 100;
};

#endif //__SWITCHDEBOUNCEHELPER_H__