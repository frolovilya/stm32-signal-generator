#include "../src/signals/Level.hpp"
#include "../src/peripherals/Peripherals.hpp"
#include "../src/shared/StringFormat.hpp"
#include "ExceptionCheck.hpp"
#include <boost/test/unit_test.hpp>
#include <functional>

BOOST_AUTO_TEST_SUITE(LevelTest)

BOOST_AUTO_TEST_CASE(stringToLevelExceptionTest) {
  const std::string exceptionMesage = stringFormat(
      "Signal level must be in the range from %d to %d mV (%d to %d dBV)",
      minLevelMv, getMaxLevelMv(), mvToDbv(minLevelMv),
      mvToDbv(getMaxLevelMv()));

  checkConversionError(&stringToLevelMv, "-100000000000000000000",
                       exceptionMesage);
  checkConversionError(&stringToLevelMv, "-1", exceptionMesage);
  checkConversionError(&stringToLevelMv, "0", exceptionMesage);
  checkConversionError(&stringToLevelMv, "2000", exceptionMesage);
  checkConversionError(&stringToLevelMv, "100000000000000000000",
                       exceptionMesage);

  checkConversionError(&stringToLevelMv, "1 mV", exceptionMesage);
  checkConversionError(&stringToLevelMv, "10v", exceptionMesage);
  checkConversionError(&stringToLevelMv, "10db", exceptionMesage);
  checkConversionError(&stringToLevelMv, "10dbp", exceptionMesage);
  checkConversionError(&stringToLevelMv, "1.234", exceptionMesage);
  checkConversionError(&stringToLevelMv, "0x1", exceptionMesage);
  checkConversionError(&stringToLevelMv, "thousand", exceptionMesage);
  checkConversionError(&stringToLevelMv, "", exceptionMesage);
}

BOOST_AUTO_TEST_CASE(stringToLevelMvSuccessTest) {
  BOOST_TEST(stringToLevelMv("1") == 1);
  BOOST_TEST(stringToLevelMv("1mv") == 1);
  BOOST_TEST(stringToLevelMv("1mV") == 1);
  
  BOOST_TEST(stringToLevelMv("23") == 23);
  BOOST_TEST(stringToLevelMv("23mv") == 23);

  BOOST_TEST(stringToLevelMv("456") == 456);
  BOOST_TEST(stringToLevelMv("456mv") == 456);
  
  BOOST_TEST(stringToLevelMv("1234") == 1234);
  BOOST_TEST(stringToLevelMv("1234mv") == 1234);

  BOOST_TEST(stringToLevelMv("0dbv") == 1414);
  BOOST_TEST(stringToLevelMv("-10dbv") == 447);

  BOOST_TEST(stringToLevelMv("0dbu") == 1096);
  BOOST_TEST(stringToLevelMv("2dbu") == 1379);

  BOOST_TEST(stringToLevelMv("1000mv") == 1000);
  BOOST_TEST(stringToLevelMv("1000mvrms") == 1414);
}

BOOST_AUTO_TEST_CASE(dbvToMvConversionTest) {
  BOOST_TEST(dbvToMv(0) == 1414);
  BOOST_TEST(dbvToMv(4) == 2242);
  BOOST_TEST(dbvToMv(-10) == 447);
  BOOST_TEST(dbvToMv(-45) == 8);
}

BOOST_AUTO_TEST_CASE(dbuToMvConversionTest) {
  BOOST_TEST(dbuToMv(0) == mvRmsToMvPeak(775));
  BOOST_TEST(dbuToMv(4) == 1737);
  BOOST_TEST(dbuToMv(-10) == 346);
}

BOOST_AUTO_TEST_CASE(mvRmsToMvConversionTest) {
  BOOST_TEST(mvRmsToMvPeak(1000) == 1414);
  BOOST_TEST(mvPeakToMvRms(1414) == 1000);
}

BOOST_AUTO_TEST_CASE(getMaxLevelTest) {
  BOOST_TEST(getMaxLevelMv() == adcInstance.getVddaMv() / 2);
}

BOOST_AUTO_TEST_CASE(getPeakToPeakTest) {
  BOOST_TEST(getPeakToPeakDigitalValue(getMaxLevelMv()) ==
             dacInstance.getMaxDigitalValue());
  BOOST_TEST(getPeakToPeakDigitalValue(getMaxLevelMv() / 2) ==
             dacInstance.getMaxDigitalValue() / 2);
  BOOST_TEST(
      getPeakToPeakDigitalValue(1000) ==
      (uint16_t)(1000.0 / getMaxLevelMv() * dacInstance.getMaxDigitalValue()));
}

BOOST_AUTO_TEST_SUITE_END()