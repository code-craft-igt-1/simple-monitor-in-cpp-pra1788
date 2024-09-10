#ifndef VITAL_CHECKS_H_
#define VITAL_CHECKS_H_

#include <functional>
#include <string>

// Function to check if a value is within a given range
bool isWithinRange(float value, float min, float max);

// Functions to check various vital signs, now including a callback for displaying warnings
bool checkTemperature(float temperature, char unit,
                      std::function<void(const std::string&)> displayWarning);
bool checkPulseRate(float pulseRate, std::function<void(const std::string&)> displayWarning);
bool checkSpo2(float spo2, std::function<void(const std::string&)> displayWarning);

#endif  // VITAL_CHECKS_H_
