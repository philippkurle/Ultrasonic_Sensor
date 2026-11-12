#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include <Arduino.h>

#define PIN_TRIGGER         22
#define PIN_ECHO            24

#define SPEED_OF_SOUND      0.0343 // in cm/µs
#define TRIGGER_SIGNAL_TIME 10     // 10µs

void setupTrigger(void);
void triggerEvent(uint32_t currentTime);

uint32_t sensorReading(void);

uint32_t calculateDistance(uint32_t measuredTime);

void updateSerialMonitor(uint32_t distance);

#endif