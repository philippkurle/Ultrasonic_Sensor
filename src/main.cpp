#include <Arduino.h>
#include "ultrasonicSensor.h"

void setup() {
  Serial.begin(115200);
  setupSensor();
}

void loop() {
  updateSensor();
}