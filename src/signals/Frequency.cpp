#include "Frequency.hpp"
#include "../peripherals/Peripherals.hpp"
#include "../shared/StringFormat.hpp"
#include <format>
#include <stdexcept>

constexpr std::string hzUnit = "hz";
constexpr std::string khzUnit = "khz";

/**
 * Returns DAC sampling rate in Hz: how many digital samples per second are
 * converted to analog signal
 */
uint32_t getSamplingRateHz() { return dacInstance.getFrequency(); }

/**
 * Convert string to frequency input taking minWaveFrequency and
 * maxWaveFrequencyHz into account
 *
 * @param str input string to parse
 * @return frequency
 */
uint16_t stringToFrequencyHz(const std::string str) {
  try {
    std::size_t unitPosition = 0;
    int newFreq = std::stoi(str, &unitPosition);

    if (unitPosition > 0 && unitPosition < str.length()) {
      std::string unitStr = str.substr(unitPosition);
      std::transform(unitStr.begin(), unitStr.end(), unitStr.begin(),
                     [](unsigned char c) { return std::tolower(c); });

      if (unitStr == khzUnit) {
        newFreq = newFreq * 1000;
      } else if (unitStr != hzUnit && unitStr != "") {
        throw std::invalid_argument("Invalid unit");
      }
    }

    if (newFreq < minWaveFrequencyHz || newFreq > maxWaveFrequencyHz) {
      throw std::invalid_argument("Out of range");
    }

    return static_cast<uint16_t>(newFreq);

  } catch (const std::exception &) {
    throw std::invalid_argument(
        stringFormat("Frequency must be in the range from %d to %d Hz",
                     minWaveFrequencyHz, maxWaveFrequencyHz));
  }
}