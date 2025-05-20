#include "../src/signals/Frequency.hpp"
#include "../src/peripherals/Peripherals.hpp"
#include "../src/shared/StringFormat.hpp"
#include "ExceptionCheck.hpp"
#include <boost/test/unit_test.hpp>
#include <functional>

BOOST_AUTO_TEST_SUITE(FrequencyTest)

BOOST_AUTO_TEST_CASE(stringToFrequencyExceptionTest) {
  const std::string exceptionMesage =
      stringFormat("Frequency must be in the range from %d to %d Hz",
                   minWaveFrequencyHz, maxWaveFrequencyHz);

  std::string invalidInputs[] = {"-100000000000000000000",
                                 "-100",
                                 "-1",
                                 "0",
                                 "19",
                                 "30001",
                                 "100000",
                                 "100000000000000000000",
                                 "1Hz",
                                 "1 Hz",
                                 "1MHz",
                                 "0x1",
                                 "fifty",
                                 ""};

  for (const std::string &input : invalidInputs) {
    checkConversionError(&stringToFrequencyHz, input, exceptionMesage);
  }
}

BOOST_AUTO_TEST_CASE(stringToFrequencySuccessTest) {
  BOOST_TEST(stringToFrequencyHz("20") == 20);
  BOOST_TEST(stringToFrequencyHz("20hz") == 20);
  BOOST_TEST(stringToFrequencyHz("20Hz") == 20);
  BOOST_TEST(stringToFrequencyHz("21") == 21);
  BOOST_TEST(stringToFrequencyHz("123") == 123);
  BOOST_TEST(stringToFrequencyHz("1kHz") == 1000);
  BOOST_TEST(stringToFrequencyHz("1234") == 1234);
  BOOST_TEST(stringToFrequencyHz("12345") == 12345);
  BOOST_TEST(stringToFrequencyHz("15kHz") == 15000);
  BOOST_TEST(stringToFrequencyHz("19999") == 19999);
  BOOST_TEST(stringToFrequencyHz("20000") == 20000);
  BOOST_TEST(stringToFrequencyHz("20kHz") == 20000);
}

BOOST_AUTO_TEST_CASE(getSamplingRateTest) {
  // Should be the same as the DAC timer frequency
  BOOST_TEST(getSamplingRateHz() == dacInstance.getFrequency());
}

BOOST_AUTO_TEST_SUITE_END()