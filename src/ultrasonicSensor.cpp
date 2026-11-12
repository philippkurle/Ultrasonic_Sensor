#include "ultrasonicSensor.h"

void setupTrigger(void){
  digitalWrite(PIN_TRIGGER, LOW);
}

void triggerEvent(uint32_t currentTime){
  static uint32_t lastTimeElapsed = 0;

  digitalWrite(PIN_TRIGGER, HIGH);

  if (currentTime >= (lastTimeElapsed + TRIGGER_SIGNAL_TIME)){
    digitalWrite(PIN_TRIGGER, LOW);
    lastTimeElapsed = currentTime;
  }
}

uint32_t sensorReading(void){
  static uint32_t timeSignalHigh = 0;
  static bool currentlyMeasuring = false;
  static bool eventRegistered = false;
  static uint32_t measuredTime = 0;

  if (!eventRegistered && digitalRead(PIN_ECHO) == HIGH){
    timeSignalHigh = micros();
    currentlyMeasuring = true;
    eventRegistered = true;
    Serial.println(F("Reading started"));
  }

  if (currentlyMeasuring && digitalRead(PIN_ECHO) == LOW){
    measuredTime = micros() - timeSignalHigh;
    timeSignalHigh = 0;
    currentlyMeasuring = false;
    eventRegistered = false;
    Serial.println(F("Echo received"));
  }
  // Serial.println(F("sensorReading function called"));
  return measuredTime;
}

uint32_t calculateDistance(uint32_t measuredTime){
  uint32_t distance = (measuredTime * SPEED_OF_SOUND)/2;
  // Serial.println(F("calculateDistance function called"));
  return distance;
}

void updateSerialMonitor(uint32_t distance){
    Serial.print(F("Distance: "));
    Serial.print(distance);
    Serial.println(F(" cm."));
}