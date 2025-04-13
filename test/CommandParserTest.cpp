#include "../src/cmd/CommandParser.hpp"
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

BOOST_AUTO_TEST_CASE(stringToFrequencySuccessTest) {
  BOOST_TEST(tryParseCommand("sine 100 1000\n") ==
             Command(WaveForm::SINE, 100, 1000));
}

BOOST_AUTO_TEST_SUITE_END()