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

// void MotorDriverMP6550::setSpeed(int16_t speed) {
//     if (speed == 1) {
//         digitalWrite(_pin_in1, HIGH);
//         digitalWrite(_pin_in2, LOW);
//     } else if (speed == -1) {
//         digitalWrite(_pin_in1, LOW);
//         digitalWrite(_pin_in2, HIGH);
//     } else if (speed == 0) {
//         digitalWrite(_pin_in1, LOW);
//         digitalWrite(_pin_in2, LOW);
//     } else if (speed >= 2) {
//         analogWrite(_pin_in1, speed);
//         analogWrite(_pin_in2, 0);
//     } else {
//         analogWrite(_pin_in1, 0);
//         analogWrite(_pin_in2, -speed);
//     }
// }

void MotorDriverMP6550::setSpeed(int16_t speed) {
    switch (speed) {
        case 1:
            digitalWrite(_pin_in1, HIGH);
            digitalWrite(_pin_in2, LOW);
            break;
        case -1:
            digitalWrite(_pin_in1, LOW);
            digitalWrite(_pin_in2, HIGH);
            break;
        case 0:
            digitalWrite(_pin_in1, LOW);
            digitalWrite(_pin_in2, LOW);
            break;
        default:
            analogWrite(_pin_in1, speed >= 2 ? speed : 0);
            analogWrite(_pin_in2, speed < 2 ? -speed : 0);
            break;
    }
}

void MotorDriverMP6550::setEnabled(bool isEnabled) {
    digitalWrite(_pin_sleep, isEnabled ? HIGH : LOW);
}

int MotorDriverMP6550::getCurrent() {
    // The current limit threshold is reached when the VISEN pin reaches 0.5V.
    // 0.5 / (limit A * 0.0001 A) = ISEN ohm
    // 450mA current limit, ISEN = 11,111 ohm
       
    // ISET = 2k resistor, VISEN = 0.2V/A (2,000 ohm * 0.0001 A)
       // current limit = 0.5/0.2 = 2.5 A

    // ISET = 5k resistor, VISEN = 0.5V/A (5,000 ohm * 0.0001 A) (ISET sources 100uA)
        // current limit = 0.5/0.5 = 1.0 A 

    // ISET = 10k resistor, VISEN = 1V/A (10,000 ohm * 0.0001 A)
       // current limit = 0.5/1.0 = 0.5 A

    int adcValue = analogRead(_pin_visen);
    float voltage = adcValue * 3.3 / 4095; // Convert ADC value to voltage (assuming a 3.3V reference)

    int voltage_int = static_cast<int>(voltage * 1000); // Convert voltage to an integer

    // Map the voltage to the corresponding current using integer values
    int current = map(voltage_int, 0, 400, 0, 320);
    
    return current;
}