#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include <Arduino.h>

#define PIN_TRIGGER          22
#define PIN_ECHO             24

#define SPEED_OF_SOUND_CM_PER_US       0.0343
#define TRIGGER_SIGNAL_TIME_US  10     // US = µs

#define TRIGGER_INTERVAL_MS 60

enum SensorState{
  STATE_IDLE,
  STATE_TRIGGER,
  STATE_MEASURING
};

void setupSensor(void);

void triggerEvent(void);

uint32_t sensorReading(void);

uint16_t calculateDistance(uint32_t measuredTimeUs);

void updateSerialMonitor(uint16_t distance);

void updateSensor(void);

#endif