#include "Frequency.hpp"
#include "../../shared/StringFormat.hpp"
#include "../peripherals/Peripherals.hpp"
#include <format>
#include <stdexcept>

uint32_t getSamplingRate() { return dacInstance.getFrequency(); }

/**
 * Convert string to frequency input taking minWaveFrequency and
 * maxWaveFrequency into account
 *
 * @param str input string to parse
 * @return frequency
 */
uint16_t stringToFrequency(const std::string str) {
  try {
    int newFreq = std::stoi(str);

    if (newFreq < minWaveFrequency || newFreq > maxWaveFrequency) {
      throw std::invalid_argument("Out of range");
    }

    return static_cast<uint16_t>(newFreq);

  } catch (const std::exception &) {
    throw std::invalid_argument(
        stringFormat("Frequency must be in the range from %d to %d Hz",
                     minWaveFrequency, maxWaveFrequency));
  }
}