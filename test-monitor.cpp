#include "./vital_checks.h"
#include "./warnings.h"

#include "gtest/gtest.h"

class VitalChecksTest : public ::testing::Test {
 protected:
  std::string lastWarning;

  void SetUp() override {
    lastWarning.clear();
  }

  void mockDisplayWarning(const std::string& message) {
    lastWarning = message;
  }

  // Generic test function for vital checks
  void testVitalCheck(bool expectedResult, double value,
                      bool (*vitalCheckFunction)(double, std::function<void(const std::string&)>),
                      const std::string& expectedWarning = "") {
    EXPECT_EQ(vitalCheckFunction(value, [this](const std::string& msgVitalCheck) {
      mockDisplayWarning(msgVitalCheck);
    }), expectedResult);
    EXPECT_EQ(lastWarning, expectedWarning);
  }

  // Test function for temperature with units
  void testTemperatureWithUnits(bool expectedResult, double temperature, char unit,
                                const std::string& expectedWarning = "") {
    EXPECT_EQ(checkTemperature(temperature, unit, [this](const std::string& msgTempTest) {
      mockDisplayWarning(msgTempTest);
    }), expectedResult);
    EXPECT_EQ(lastWarning, expectedWarning);
  }
};

// Test Cases for Temperature Checks
TEST_F(VitalChecksTest, TemperatureWithinLimit) {
  testTemperatureWithUnits(true, 98.0, 'F');  // Within limit
}

TEST_F(VitalChecksTest, TemperatureAboveLimit) {
  testTemperatureWithUnits(false, 100.0, 'F', "Approaching hyperthermia");  // Above limit
}

TEST_F(VitalChecksTest, TemperatureFarAboveLimit) {
  testTemperatureWithUnits(false, 104.0, 'F', "Approaching hyperthermia");  // Far above limit
}

// Early Warning Test Cases for Temperature
TEST_F(VitalChecksTest, TemperatureEarlyWarningLow) {
  // Assuming early warning is triggered at 95.0 + warningThreshold
  testTemperatureWithUnits(false, 96.0, 'F', "Approaching hypothermia");  // Early warning
}

TEST_F(VitalChecksTest, TemperatureEarlyWarningHigh) {
  // Assuming early warning is triggered at 102.0 - warningThreshold
  testTemperatureWithUnits(false, 101.0, 'F', "Approaching hyperthermia");  // Early warning
}

// Test Cases for Pulse Rate Checks
TEST_F(VitalChecksTest, PulseRateWithinLimit) {
  testVitalCheck(true, 75.0, checkPulseRate);  // Within limit
}

TEST_F(VitalChecksTest, PulseRateBelowLimit) {
  testVitalCheck(false, 55.0, checkPulseRate, "Pulse Rate is too low!");  // Below limit
}

TEST_F(VitalChecksTest, PulseRateFarBelowLimit) {
  testVitalCheck(false, 40.0, checkPulseRate, "Pulse Rate is too low!");  // Far below limit
}

// Early Warning Test Cases for Pulse Rate
TEST_F(VitalChecksTest, PulseRateEarlyWarningLow) {
  // Assuming early warning is triggered at 60.0 - warningThreshold
  testVitalCheck(false, 59.0, checkPulseRate, "Pulse Rate is too low!");  // Early warning
}

TEST_F(VitalChecksTest, PulseRateEarlyWarningHigh) {
  // Assuming early warning is triggered at 100.0 + warningThreshold
  testVitalCheck(false, 101.0, checkPulseRate, "Pulse Rate is too high!");  // Early warning
}

// Test Cases for SpO2 Checks
TEST_F(VitalChecksTest, Spo2WithinLimit) {
  testVitalCheck(true, 95.0, checkSpo2);  // Within limit
}

TEST_F(VitalChecksTest, Spo2BelowLimit) {
  testVitalCheck(false, 85.0, checkSpo2, "Approaching hypoxemia");  // Below limit
}

TEST_F(VitalChecksTest, Spo2FarBelowLimit) {
  testVitalCheck(false, 70.0, checkSpo2, "Approaching hypoxemia");  // Far below limit
}

// Early Warning Test Cases for SpO2
TEST_F(VitalChecksTest, Spo2EarlyWarning) {
  // Assuming early warning is triggered at 90.0 - warningThreshold
  testVitalCheck(false, 89.0, checkSpo2, "Approaching hypoxemia");  // Early warning
}

// Temperature Conversion Test Cases
TEST_F(VitalChecksTest, CelsiusToFahrenheitConversion) {
  double celsius = 37.0;  // Normal body temperature in Celsius
  double fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
  testTemperatureWithUnits(true, fahrenheit, 'F');  // Within limit
}

TEST_F(VitalChecksTest, FahrenheitToCelsiusConversion) {
  double fahrenheit = 98.0;  // Normal body temperature in Fahrenheit
  double celsius = (fahrenheit - 32.0) * 5.0 / 9.0;
  testTemperatureWithUnits(true, celsius, 'C');  // Within limit
}

// Main function for running all test cases
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
