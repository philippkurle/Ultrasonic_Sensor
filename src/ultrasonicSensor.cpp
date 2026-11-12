#include "ultrasonicSensor.h"

void setupSensor(void){
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIGGER, LOW);
}

void triggerEvent(void){
  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(TRIGGER_SIGNAL_TIME_US);
  digitalWrite(PIN_TRIGGER, LOW);
}

// ### TODO: Lösung Messung timeout, zB wenn nach 30ms Echo noch nicht LOW wird?
// ### möglicher Ansatz: STATE_MEASURING in zwei Zustände aufteilen, „Warten auf Echo HIGH“ und „Warten auf Echo LOW“
uint32_t sensorReading(void){
  static uint32_t echoStartUs = 0;
  static bool currentlyMeasuring = false;

  if (!currentlyMeasuring && digitalRead(PIN_ECHO) == HIGH){
    echoStartUs = micros();
    currentlyMeasuring = true;
  }

  if (currentlyMeasuring && digitalRead(PIN_ECHO) == LOW){
    uint32_t measuredTimeUs = micros() - echoStartUs;
    currentlyMeasuring = false;
    return measuredTimeUs;
  }

  return 0;
}

uint16_t calculateDistance(uint32_t measuredTimeUs){
  uint16_t distance = (measuredTimeUs * SPEED_OF_SOUND_CM_PER_US)/2;
  return distance;
}

void updateSerialMonitor(uint16_t distance){
    Serial.print(F("Distance: "));
    Serial.print(distance);
    Serial.println(F(" cm."));
}

void updateSensor(void){
  static SensorState currentState = STATE_IDLE;
  static uint32_t lastTriggerMs = 0;

  switch (currentState){
    case STATE_IDLE:
      if (millis() - lastTriggerMs >= TRIGGER_INTERVAL_MS && digitalRead(PIN_ECHO) == LOW){
        lastTriggerMs = millis();
        currentState = STATE_TRIGGER;
      }
      break;
    case STATE_TRIGGER:
      triggerEvent();
      currentState = STATE_MEASURING;
      break;
    case STATE_MEASURING: {
      uint32_t measuredTimeUs = sensorReading();
      if (measuredTimeUs != 0){
        updateSerialMonitor(calculateDistance(measuredTimeUs));
        currentState = STATE_IDLE;
      }
      break;
    }  
  }
}