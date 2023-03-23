#include "MotorDriverMP6550.h"

MotorDriverMP6550::MotorDriverMP6550(uint8_t pin_sleep, uint8_t pin_in1, uint8_t pin_in2, uint8_t pin_visen) {
    _pin_sleep = pin_sleep;
    _pin_in1 = pin_in1;
    _pin_in2 = pin_in2;
    _pin_visen = pin_visen;
}

void MotorDriverMP6550::begin() {
    pinMode(_pin_sleep, OUTPUT);
    pinMode(_pin_in1, OUTPUT);
    pinMode(_pin_in2, OUTPUT);
    pinMode(_pin_visen, INPUT);

    setEnabled(false);
}

void MotorDriverMP6550::setSpeed(int16_t speed) {
    if (speed >= 0) {
        analogWrite(_pin_in1, speed);
        analogWrite(_pin_in2, 0);
    } else {
        analogWrite(_pin_in1, 0);
        analogWrite(_pin_in2, -speed);
    }
}

void MotorDriverMP6550::setEnabled(bool isEnabled) {
    digitalWrite(_pin_sleep, isEnabled ? HIGH : LOW);
}

float MotorDriverMP6550::getCurrent() {
    // The current limit threshold is reached when the VISEN pin reaches 0.5V.
    //example: ISET = 5k resistor, VISEN = 0.5V/A (5,000 ohm * 0.0001 A) (ISET sources 100uA)
        // current limit = 0.5/0.5 = 1.0 A    
    
    // ISET = 2k resistor, VISEN = 0.2V/A (2,000 ohm * 0.0001 A)
       // current limit = 0.5/0.2 = 2.5 A

    // ISET = 10k resistor, VISEN = 1V/A (10,000 ohm * 0.0001 A)
       // current limit = 0.5/1.0 = 0.5 A

    int adcValue = analogRead(_pin_visen);
    float voltage = (float)adcValue * 3.3 / 4095; // Convert ADC value to voltage (assuming a 3.3V reference)
    float current = voltage / 0.200; // Convert voltage to current based on the typical VISEN scaling factor (0.200 V/A)
    
    return current;
}