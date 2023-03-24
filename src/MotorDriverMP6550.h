#ifndef MOTORDRIVERMP6550_H
#define MOTORDRIVERMP6550_H

#include "Particle.h"

class MotorDriverMP6550 {
public:
    MotorDriverMP6550(uint8_t pin_sleep, uint8_t pin_in1, uint8_t pin_in2, uint8_t pin_visen);

    void begin();
    void setSpeed(int16_t speed);
    void setEnabled(bool isEnabled);
    int getCurrent();

private:
    uint8_t _pin_sleep;
    uint8_t _pin_in1;
    uint8_t _pin_in2;
    uint8_t _pin_visen;
};

#endif