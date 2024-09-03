// vital_checks.cpp
#include "./vital_checks.h"
#include "./warnings.h"

// Constants for vital limits
const float MAX_TEMPERATURE_IN_F = 102.0;
const float MIN_TEMPERATURE_IN_F = 95.0;
const float MIN_PULSE_RATE_PER_MIN = 60.0;
const float MAX_PULSE_RATE_PER_MIN = 100.0;
const float MIN_SPO2 = 90.0;

// Function to check if a value is within a given range
bool isTemperatureWithinRange(float value, float min, float max) {
    return (value >= min && value <= max);
}

// Function to check temperature and display warning if needed
bool checkTemperature(float temperature) {
    if (!isTemperatureWithinRange(temperature, MIN_TEMPERATURE_IN_F, MAX_TEMPERATURE_IN_F)) {
        displayWarning("Temperature is critical!");
        return false;
    }
    return true;
}

// Function to check pulse rate and display warning if needed
bool checkPulseRate(float pulseRate) {
    if (!isTemperatureWithinRange(pulseRate, MIN_PULSE_RATE_PER_MIN, MAX_PULSE_RATE_PER_MIN)) {
        displayWarning("Pulse Rate is out of range!");
        return false;
    }
    return true;
}

// Function to check oxygen saturation and display warning if needed
bool checkSpo2(float spo2) {
    if (spo2 < MIN_SPO2) {
        displayWarning("Oxygen Saturation out of range!");
        return false;
    }
    return true;
}
