#include <Arduino.h>
#include "ultrasonicSensor.h"

void setup() {
  Serial.begin(115200);

  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  setupTrigger();
}

void loop() {
  uint32_t now = micros();
  triggerEvent(now);

  uint32_t measuredTime = sensorReading();
  uint32_t distance = calculateDistance(measuredTime);

  updateSerialMonitor(distance);

  delay(60);
}