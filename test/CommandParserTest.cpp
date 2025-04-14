#include "../src/cmd/CommandParser.hpp"
#include "../src/shared/StringFormat.hpp"
#include "../src/signals/Frequency.hpp"
#include "../src/signals/Level.hpp"
#include "ExceptionCheck.hpp"
#include <boost/test/unit_test.hpp>
#include <functional>

namespace boost {
namespace test_tools {
namespace tt_detail {
template <> struct print_log_value<Command> {
  void operator()(std::ostream &os, Command const &c) { os << c; }
};
} // namespace tt_detail
} // namespace test_tools
} // namespace boost

BOOST_AUTO_TEST_SUITE(CommandParserTest)

BOOST_AUTO_TEST_CASE(parseCommandSuccessTest) {
  BOOST_TEST(parseCommand("sine 100 1000") ==
             Command(WaveForm::SINE, 100, 1000));

  BOOST_TEST(parseCommand("square 50 555") ==
             Command(WaveForm::SQUARE, 50, 555));

  BOOST_TEST(parseCommand("saw 25000 1450") ==
             Command(WaveForm::SAW, 25000, 1450));

  BOOST_TEST(parseCommand("triangle 444 999") ==
             Command(WaveForm::TRIANGLE, 444, 999));
}

BOOST_AUTO_TEST_CASE(parseCommandExceptionTest) {
  checkConversionError(&parseCommand, "", getUsageHelp());
  checkConversionError(&parseCommand, "sine", getUsageHelp());
  checkConversionError(&parseCommand, "sine 50", getUsageHelp());

  // checking that other exceptions are also propagating
  const std::string frequencyRange =
      stringFormat("Frequency must be in the range from %d to %d Hz",
                   minWaveFrequencyHz, maxWaveFrequencyHz);
  checkConversionError(&parseCommand, "sine 500000 1000", frequencyRange);

  const std::string levelRange =
      stringFormat("Signal level must be in the range from %d to %d mV",
                   minLevelMV, getMaxLevelMV());
  checkConversionError(&parseCommand, "sine 440 220000", levelRange);
}

BOOST_AUTO_TEST_SUITE_END()