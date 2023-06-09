/*
 * Project 20_New_Motor
 * Description: Testing worm gear motor using the MP6650 motor controller
 * Date: 03/21/2023
 * Version: 1
 */

#include "Particle.h"
#include "MotorDriverMP6550.h"

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);
// SerialLogHandler logHandler(LOG_LEVEL_ALL);

// Define the motor driver pins
constexpr uint8_t PIN_SLEEP = D2;
constexpr uint8_t PIN_IN1 = A4;
constexpr uint8_t PIN_IN2 = A5;
constexpr uint8_t PIN_VISEN = A0;

MotorDriverMP6550 motorDriver(PIN_SLEEP, PIN_IN1, PIN_IN2, PIN_VISEN);

int controlMotor(String command);

void setup() {
    Particle.function("controlMotor", controlMotor);
    Particle.connect();
    Serial.begin(9600);

    motorDriver.begin();
}

void loop() {
    int current = motorDriver.getCurrent();
    Serial.printlnf("Current: %u mA", current);
    delay(1000);
}

int controlMotor(String command) {
    int16_t speed = command.toInt();

    if (speed < -255) speed = -255;
    else if (speed > 255) speed = 255;
    
    if (speed == 0) {
        motorDriver.setEnabled(false);
        motorDriver.setSpeed(speed);
        return speed;
    } else {
        motorDriver.setEnabled(true);
        motorDriver.setSpeed(speed);
        return speed;
    }
}