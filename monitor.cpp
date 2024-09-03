// main.cpp
#include "./monitor.h"
#include "./vital_checks.h"

// Main function to check all vitals
int vitalsOk(float temperature, float pulseRate, float spo2) {
    bool tempOk = checkTemperature(temperature);
    bool pulseOk = checkPulseRate(pulseRate);
    bool spo2Ok = checkSpo2(spo2);

    return tempOk && pulseOk && spo2Ok;
}
