// vital_checks.h
#ifndef VITAL_CHECKS_H_
#define VITAL_CHECKS_H_

#include <string>

bool isWithinRange(float value, float min, float max);
bool checkTemperature(float temperature);
bool checkPulseRate(float pulseRate);
bool checkSpo2(float spo2);

#endif  // VITAL_CHECKS_H_
