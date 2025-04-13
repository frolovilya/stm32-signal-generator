#include "../src/signals/Frequency.hpp"
#include "../shared/StringFormat.hpp"
#include "../src/peripherals/Peripherals.hpp"
#include "ExceptionCheck.hpp"
#include <boost/test/unit_test.hpp>
#include <functional>

BOOST_AUTO_TEST_SUITE(FrequencyTest)

BOOST_AUTO_TEST_CASE(stringToFrequencyExceptionTest) {
  const std::string exceptionMesage =
      stringFormat("Frequency must be in the range from %d to %d Hz",
                   minWaveFrequencyHz, maxWaveFrequencyHz);

  checkConversionError(&stringToFrequencyHz, "-100000000000000000000",
                       exceptionMesage);
  checkConversionError(&stringToFrequencyHz, "-1", exceptionMesage);
  checkConversionError(&stringToFrequencyHz, "0", exceptionMesage);
  checkConversionError(&stringToFrequencyHz, "19", exceptionMesage);
  checkConversionError(&stringToFrequencyHz, "30001", exceptionMesage);
  checkConversionError(&stringToFrequencyHz, "100000", exceptionMesage);
  checkConversionError(&stringToFrequencyHz, "100000000000000000000",
                       exceptionMesage);

  checkConversionError(&stringToFrequencyHz, "1Hz", exceptionMesage);
  checkConversionError(&stringToFrequencyHz, "1 Hz", exceptionMesage);
  checkConversionError(&stringToFrequencyHz, "0x1", exceptionMesage);
  checkConversionError(&stringToFrequencyHz, "fifty", exceptionMesage);
  checkConversionError(&stringToFrequencyHz, "", exceptionMesage);
}

BOOST_AUTO_TEST_CASE(stringToFrequencySuccessTest) {
  BOOST_TEST(stringToFrequencyHz("20") == 20);
  BOOST_TEST(stringToFrequencyHz("21") == 21);
  BOOST_TEST(stringToFrequencyHz("123") == 123);
  BOOST_TEST(stringToFrequencyHz("1234") == 1234);
  BOOST_TEST(stringToFrequencyHz("12345") == 12345);
  BOOST_TEST(stringToFrequencyHz("29999") == 29999);
  BOOST_TEST(stringToFrequencyHz("30000") == 30000);
}

BOOST_AUTO_TEST_CASE(getSamplingRateTest) {
  // Should be the same as the DAC timer frequency
  BOOST_TEST(getSamplingRateHz() == dacInstance.getFrequency());
}

BOOST_AUTO_TEST_SUITE_END()