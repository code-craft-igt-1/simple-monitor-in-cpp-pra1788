#include "./vital_checks.h"
#include "./warnings.h"

#include "gtest/gtest.h"

// Test fixture class for Vital Checks
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
    EXPECT_EQ(vitalCheckFunction(value, [this](const std::string& msg) {
      mockDisplayWarning(msg);
    }), expectedResult);
    EXPECT_EQ(lastWarning, expectedWarning);
  }
};

// Test Cases for Temperature Checks
TEST_F(VitalChecksTest, TemperatureWithinLimit) {
  testVitalCheck(true, 98.0, checkTemperature);  // Within limit
}

TEST_F(VitalChecksTest, TemperatureAboveLimit) {
  testVitalCheck(false, 100.0, checkTemperature, "Temperature is too high!");  // Above limit
}

TEST_F(VitalChecksTest, TemperatureFarAboveLimit) {
  testVitalCheck(false, 104.0, checkTemperature, "Temperature is too high!");  // Far above limit
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

// Test Cases for SpO2 Checks
TEST_F(VitalChecksTest, Spo2WithinLimit) {
  testVitalCheck(true, 95.0, checkSpo2);  // Within limit
}

TEST_F(VitalChecksTest, Spo2BelowLimit) {
  testVitalCheck(false, 85.0, checkSpo2, "SpO2 is too low!");  // Below limit
}

TEST_F(VitalChecksTest, Spo2FarBelowLimit) {
  testVitalCheck(false, 70.0, checkSpo2, "SpO2 is too low!");  // Far below limit
}

// Main function for running all test cases
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
