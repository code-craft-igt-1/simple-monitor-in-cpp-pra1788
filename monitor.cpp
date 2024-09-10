#include "./monitor.h"
#include "./vital_checks.h"
#include "./warnings.h"

#include <string>
#include <iostream>

using std::cout;
using std::endl;

// Function to display a default warning
void defaultWarning(const std::string& message) {
    // Example implementation of displayWarning
    // This function should be implemented or linked properly
    // For now, it just prints the warning message
    cout << "Warning: " << message << endl;
}

// Main function to check all vitals
bool vitalsOk(float temperature, float pulseRate, float spo2, char tempUnit = 'F') {
    bool tempOk = checkTemperature(temperature, tempUnit, defaultWarning);
    bool pulseOk = checkPulseRate(pulseRate, defaultWarning);
    bool spo2Ok = checkSpo2(spo2, defaultWarning);

    return tempOk && pulseOk && spo2Ok;
}
