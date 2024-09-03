#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>

using std::cout;
using std::flush;
using std::this_thread::sleep_for;
using std::chrono::seconds;

// Constants for vital limits
const float MAX_TEMPERATURE = 102.0;
const float MIN_TEMPERATURE = 95.0;
const float MIN_PULSE_RATE = 60.0;
const float MAX_PULSE_RATE = 100.0;
const float MIN_SPO2 = 90.0;

// Function to check if temperature is within the safe range
bool isTemperatureNormal(float temperature) {
    return (temperature <= MAX_TEMPERATURE && temperature >= MIN_TEMPERATURE);
}

// Function to check if pulse rate is within the safe range
bool isPulseRateNormal(float pulseRate) {
    return (pulseRate >= MIN_PULSE_RATE && pulseRate <= MAX_PULSE_RATE);
}

// Function to check if oxygen saturation is within the safe range
bool isSpo2Normal(float spo2) {
    return (spo2 >= MIN_SPO2);
}

// Function to display blinking pattern
void displayWarning(const std::string& message) {
    cout << message << "\n";
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

// Function to check all vitals and print warnings if needed
int vitalsOk(float temperature, float pulseRate, float spo2) {
    if (!isTemperatureNormal(temperature)) {
        displayWarning("Temperature is critical!");
        return 0;
    } 
    if (!isPulseRateNormal(pulseRate)) {
        displayWarning("Pulse Rate is out of range!");
        return 0;
    } 
    if (!isSpo2Normal(spo2)) {
        displayWarning("Oxygen Saturation out of range!");
        return 0;
    }
    return 1;
}
