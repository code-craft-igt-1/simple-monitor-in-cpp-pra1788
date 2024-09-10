#include "./vital_checks.h"
#include <functional>
#include <string>

// Constants for vital limits in Fahrenheit
const float MAX_TEMPERATURE_IN_F = 102.0;
const float MIN_TEMPERATURE_IN_F = 95.0;
const float MIN_PULSE_RATE_PER_MIN = 60.0;
const float MAX_PULSE_RATE_PER_MIN = 100.0;
const float MIN_SPO2 = 90.0;

// Warning tolerance percentage
const float WARNING_TOLERANCE_PERCENT = 1.5 / 100.0;

// Function to calculate warning threshold
float calculateWarningThreshold(float upperLimit) {
    return upperLimit * WARNING_TOLERANCE_PERCENT;
}

// Function to check if a value is within a given range
bool isWithinRange(float value, float min, float max) {
    return (value >= min && value <= max);
}

// Helper function for generating warning messages
bool checkLow(float value, float min, float warningThreshold,
               const std::string& message,
               std::function<void(const std::string&)> displayWarning) {
    if (value < min + warningThreshold) {
        displayWarning(message);
        return false;
    }
    return true;
}

bool checkHigh(float value, float max, float warningThreshold,
            const std::string& message, std::function<void(const std::string&)> displayWarning) {
    if (value > max - warningThreshold) {
        displayWarning(message);
        return false;
    }
    return true;
}

bool checkInRange(float value, float min, float max, const std::string& message,
                  std::function<void(const std::string&)> displayWarning) {
    if (!isWithinRange(value, min, max)) {
        displayWarning(message);
        return false;
    }
    return true;
}

// Consolidated function to check vital signs
bool checkVital(float value, float min, float max, float warningThreshold,
                const std::string& lowMessage, const std::string& highMessage,
                std::function<void(const std::string&)> displayWarning) {
    if (!checkLow(value, min, warningThreshold, lowMessage, displayWarning)) {
        return false;
    }

    if (!checkHigh(value, max, warningThreshold, highMessage, displayWarning)) {
        return false;
    }

    return checkInRange(value, min, max, "Value is out of range!", displayWarning);
}

// Conversion functions
float toFahrenheit(float celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

// Function to check temperature with unit conversion
bool checkTemperature(float temperature, char unit,
                      std::function<void(const std::string&)> displayWarning) {
    // Convert temperature to Fahrenheit if unit is Celsius
    float temperatureInFahrenheit = (unit == 'C') ? toFahrenheit(temperature) : temperature;
    float warningThreshold = calculateWarningThreshold(MAX_TEMPERATURE_IN_F);

    return checkVital(temperatureInFahrenheit, MIN_TEMPERATURE_IN_F, MAX_TEMPERATURE_IN_F,
                      warningThreshold, "Approaching hypothermia",
                      "Approaching hyperthermia", displayWarning);
}

// Function to check pulse rate
bool checkPulseRate(float pulseRate,
                    std::function<void(const std::string&)> displayWarning) {
    float warningThreshold = calculateWarningThreshold(MAX_PULSE_RATE_PER_MIN);

    return checkVital(pulseRate, MIN_PULSE_RATE_PER_MIN, MAX_PULSE_RATE_PER_MIN,
                      warningThreshold, "Pulse Rate is too low!",
                      "Pulse Rate is too high!", displayWarning);
}

// Function to check SPO2
bool checkSpo2(float spo2,
                std::function<void(const std::string&)> displayWarning) {
    float warningThreshold = calculateWarningThreshold(MIN_SPO2);

    if (spo2 < MIN_SPO2 + warningThreshold) {
        displayWarning("Approaching hypoxemia");
        return false;
    }

    return checkInRange(spo2, MIN_SPO2, 100.0, "Oxygen Saturation is too low!",
                        displayWarning);
}
