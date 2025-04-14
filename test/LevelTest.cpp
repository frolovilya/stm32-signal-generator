#include "../src/signals/Level.hpp"
#include "../src/peripherals/Peripherals.hpp"
#include "../src/shared/StringFormat.hpp"
#include "ExceptionCheck.hpp"
#include <boost/test/unit_test.hpp>
#include <functional>

BOOST_AUTO_TEST_SUITE(LevelTest)

BOOST_AUTO_TEST_CASE(stringToLevelExceptionTest) {
  const std::string exceptionMesage =
      stringFormat("Signal level must be in the range from %d to %d mV",
                   minLevelMV, getMaxLevelMV());

  checkConversionError(&stringToLevelMV, "-100000000000000000000",
                       exceptionMesage);
  checkConversionError(&stringToLevelMV, "-1", exceptionMesage);
  checkConversionError(&stringToLevelMV, "0", exceptionMesage);
  checkConversionError(&stringToLevelMV, "1", exceptionMesage);
  checkConversionError(&stringToLevelMV, "2000", exceptionMesage);
  checkConversionError(&stringToLevelMV, "100000000000000000000",
                       exceptionMesage);

  checkConversionError(&stringToLevelMV, "1mV", exceptionMesage);
  checkConversionError(&stringToLevelMV, "1 mV", exceptionMesage);
  checkConversionError(&stringToLevelMV, "0x1", exceptionMesage);
  checkConversionError(&stringToLevelMV, "thousand", exceptionMesage);
  checkConversionError(&stringToLevelMV, "", exceptionMesage);
}

BOOST_AUTO_TEST_CASE(stringToLevelSuccessTest) {
  BOOST_TEST(stringToLevelMV("2") == 2);
  BOOST_TEST(stringToLevelMV("12") == 12);
  BOOST_TEST(stringToLevelMV("123") == 123);
  BOOST_TEST(stringToLevelMV("1234") == 1234);
}

BOOST_AUTO_TEST_CASE(getMaxLevelTest) {
  BOOST_TEST(getMaxLevelMV() == adcInstance.getVddaMV() / 2);
}

BOOST_AUTO_TEST_CASE(getPeakToPeakTest) {
  BOOST_TEST(getPeakToPeakDigitalValue(getMaxLevelMV()) ==
             dacInstance.getMaxDigitalValue());
  BOOST_TEST(getPeakToPeakDigitalValue(getMaxLevelMV() / 2) ==
             dacInstance.getMaxDigitalValue() / 2);
  BOOST_TEST(
      getPeakToPeakDigitalValue(1000) ==
      (uint16_t)(1000.0 / getMaxLevelMV() * dacInstance.getMaxDigitalValue()));
}

BOOST_AUTO_TEST_SUITE_END()