#include "Level.hpp"
#include "../peripherals/Peripherals.hpp"
#include "../shared/StringFormat.hpp"
#include <stdexcept>

/**
 * Max signal level in mV that the DAC is able to generate
 */
uint16_t getMaxLevelMV() { return (adcInstance.getVddaMV() - 200) / 2; }

/**
 * Get Peak-to-Peak (signal level in mV x2) value for DAC
 */
uint16_t getPeakToPeakDigitalValue(uint16_t signalLevelMV) {
  return (double)signalLevelMV / getMaxLevelMV() *
         dacInstance.getMaxDigitalValue();
}

/**
 * Convert string to level value in mV taking minLevelMV and
 * maxLevelMV into account
 *
 * @param str input string to parse
 * @return signal level in mV
 */
uint16_t stringToLevelMV(const std::string str) {
  try {
    int newLevelMV = std::stoi(str);

    if (newLevelMV < minLevelMV || newLevelMV > getMaxLevelMV()) {
      throw std::invalid_argument("Out of range");
    }

    return static_cast<uint16_t>(newLevelMV);

  } catch (const std::exception &e) {
    throw std::invalid_argument(
        stringFormat("Signal level must be in the range from %d to %d mV",
                     minLevelMV, getMaxLevelMV()));
  }
}