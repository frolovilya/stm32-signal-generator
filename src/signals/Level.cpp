#include "Level.hpp"
#include "../peripherals/Peripherals.hpp"
#include "../shared/StringFormat.hpp"
#include <cmath>
#include <stdexcept>

constexpr std::string dbvUnit = "dbv";
constexpr std::string dbuUnit = "dbu";
constexpr std::string mvUnit = "mv";
constexpr std::string mvRmsUnit = "mvrms";

// Voltage to send 1 mW through 600 Ohm load
// P = UI, I = U / R, P = U^2 / R, U = sqrt(P * R)
// U = sqrt(0.001 * 600) = 0.775
constexpr double dbuMultiplier = 0.775;

/**
 * Max signal level in mV that the DAC is able to generate
 */
uint16_t getMaxLevelMv() { return adcInstance.getVddaMv() / 2; }

/**
 * Get Peak-to-Peak (signal level in mV x2) value for DAC
 */
uint16_t getPeakToPeakDigitalValue(const uint16_t signalLevelMv) {
  return (double)signalLevelMv / getMaxLevelMv() *
         dacInstance.getMaxDigitalValue();
}

/**
 * Convert string to level value in mV taking minLevelMv and
 * maxLevelMV into account
 *
 * @param str input string to parse
 * @return signal level in mV
 */
uint16_t stringToLevelMv(const std::string str) {
  try {
    std::size_t unitPosition = 0;
    int newLevelMv = std::stoi(str, &unitPosition);

    if (unitPosition > 0 && unitPosition < str.length()) {
      std::string unitStr = str.substr(unitPosition);
      std::transform(unitStr.begin(), unitStr.end(), unitStr.begin(),
                     [](unsigned char c) { return std::tolower(c); });

      if (unitStr == dbvUnit) {
        newLevelMv = dbvToMv(newLevelMv);
      } else if (unitStr == dbuUnit) {
        newLevelMv = dbuToMv(newLevelMv);
      } else if (unitStr == mvRmsUnit) {
        newLevelMv = mvRmsToMvPeak(newLevelMv);
      } else if (unitStr != mvUnit) {
        throw std::invalid_argument("Invalid unit");
      }
    }

    if (newLevelMv < minLevelMv || newLevelMv > getMaxLevelMv()) {
      throw std::invalid_argument("Value out of range");
    }

    return static_cast<uint16_t>(newLevelMv);

  } catch (const std::exception &e) {
    throw std::invalid_argument(stringFormat(
        "Signal level must be in the range from %d to %d mV (%d to %d dBV)",
        minLevelMv, getMaxLevelMv(), mvToDbv(minLevelMv),
        mvToDbv(getMaxLevelMv())));
  }
}

/**
 * Convert signal level in mV peak to mV RMS
 */
uint16_t mvPeakToMvRms(const uint16_t signalLevelMv) {
  return std::round(signalLevelMv / std::sqrt(2));
}

/**
 * Convert signal level in mV RMS to mV peak
 */
uint16_t mvRmsToMvPeak(const uint16_t signalLevelMvRms) {
  return std::round(signalLevelMvRms * std::sqrt(2));
}

/**
 * Convert signal level in mV peak to dBV
 */
int16_t mvToDbv(const uint16_t signalLevelMv) {
  return std::round(20.0 * std::log10(mvPeakToMvRms(signalLevelMv) / 1000.0));
}

/**
 * Convert signal level in dBV to mV peak
 */
uint16_t dbvToMv(const int16_t signalLevelDbv) {
  return mvRmsToMvPeak(std::round(std::pow(10, signalLevelDbv / 20.0) * 1000.0));
}

/**
 * Convert signal level in mV peak to dBu
 */
int16_t mvToDbu(const uint16_t signalLevelMv) {
  return std::round(20.0 * std::log10(mvPeakToMvRms(signalLevelMv) / 1000.0 / dbuMultiplier));
}

/**
 * Convert signal level in dBu to mV peak
 */
uint16_t dbuToMv(const int16_t signalLevelDbu) {
  return mvRmsToMvPeak(std::pow(10, signalLevelDbu / 20.0) * 1000.0 * dbuMultiplier);
}
