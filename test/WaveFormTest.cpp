#include "../src/signals/WaveForm.hpp"
#include "../src/peripherals/Peripherals.hpp"
#include "../src/shared/StringFormat.hpp"
#include "ExceptionCheck.hpp"
#include <boost/test/unit_test.hpp>

namespace boost {
namespace test_tools {
namespace tt_detail {
template <> struct print_log_value<WaveForm> {
  void operator()(std::ostream &os, WaveForm const &waveForm) {
    os << waveFormToString(waveForm);
  }
};
} // namespace tt_detail
} // namespace test_tools
} // namespace boost

BOOST_AUTO_TEST_SUITE(WaveFormTest)

BOOST_AUTO_TEST_CASE(stringToWaveFormSuccessTest) {
  BOOST_TEST(stringToWaveForm("sine") == WaveForm::SINE);
  BOOST_TEST(stringToWaveForm("square") == WaveForm::SQUARE);
  BOOST_TEST(stringToWaveForm("saw") == WaveForm::SAW);
  BOOST_TEST(stringToWaveForm("triangle") == WaveForm::TRIANGLE);
}

BOOST_AUTO_TEST_CASE(stringToWaveFormExceptionTest) {
  checkConversionError(&stringToWaveForm, "SINE",
                       "Unable to convert 'SINE' to WaveForm enum");
  checkConversionError(&stringToWaveForm, "",
                       "Unable to convert '' to WaveForm enum");
}

BOOST_AUTO_TEST_SUITE_END()