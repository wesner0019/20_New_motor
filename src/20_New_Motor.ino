/*
 * Project 20_New_Motor
 * Description: Testing worm gear motor using the MP6650 motor controller
 * Date: 03/21/2023
 */

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);
SerialLogHandler logHandler(LOG_LEVEL_ALL);

uint8_t firmVersion = 82;

const pin_t doneWDTSignal = C0;

void setup() {
  pinMode(CoverButton, INPUT_PULLUP);
  Serial.begin(9600);
}


void loop() {

}