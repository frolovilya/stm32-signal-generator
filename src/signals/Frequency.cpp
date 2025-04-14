#include "Frequency.hpp"
#include "../peripherals/Peripherals.hpp"
#include "../shared/StringFormat.hpp"
#include <format>
#include <stdexcept>

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
    int newFreq = std::stoi(str);

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