#include "../src/signals/Frequency.hpp"
#include "../shared/StringFormat.hpp"
#include <boost/test/unit_test.hpp>
#include <functional>

BOOST_AUTO_TEST_SUITE(FrequencyTest)

void checkError(std::function<uint16_t(const std::string)> conversionFunction,
                std::string input, const std::string expectedExceptionText) {
  try {
    conversionFunction(input);
    BOOST_ERROR("Expecting conversion to fail");
  } catch (const std::exception &e) {
    BOOST_TEST(e.what() == expectedExceptionText);
  }
}

BOOST_AUTO_TEST_CASE(stringToFrequencyExceptionTest) {
  const std::string exceptionMesage =
      stringFormat("Frequency must be in the range from %d to %d Hz",
                   minWaveFrequency, maxWaveFrequency);

  checkError(&stringToFrequency, "-100000000000000000000", exceptionMesage);
  checkError(&stringToFrequency, "-1", exceptionMesage);
  checkError(&stringToFrequency, "0", exceptionMesage);
  checkError(&stringToFrequency, "19", exceptionMesage);
  checkError(&stringToFrequency, "30001", exceptionMesage);
  checkError(&stringToFrequency, "100000", exceptionMesage);
  checkError(&stringToFrequency, "100000000000000000000", exceptionMesage);
}

BOOST_AUTO_TEST_CASE(stringToFrequencyTest) {
  BOOST_TEST(stringToFrequency("20") == 20);
  BOOST_TEST(stringToFrequency("21") == 21);
  BOOST_TEST(stringToFrequency("123") == 123);
  BOOST_TEST(stringToFrequency("1234") == 1234);
  BOOST_TEST(stringToFrequency("12345") == 12345);
  BOOST_TEST(stringToFrequency("29999") == 29999);
  BOOST_TEST(stringToFrequency("30000") == 30000);
}

BOOST_AUTO_TEST_CASE(getSamplingRateTest) {
  // Should be the same as the DAC timer frequency
  BOOST_TEST(getSamplingRate() == 1000000);
}

BOOST_AUTO_TEST_SUITE_END()