#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <cstdint>
#include <string>

constexpr uint16_t minLevelMv = 1;
uint16_t getMaxLevelMv();
constexpr uint16_t defaultLevelMv = 447; // -10dbV

uint16_t getPeakToPeakDigitalValue(const uint16_t signalLevelMv);
uint16_t stringToLevelMv(const std::string str);

int16_t mvToDbv(const uint16_t signalLevelMv);
uint16_t dbvToMv(const int16_t signalLevelDbv);

int16_t mvToDbu(const uint16_t signalLevelMv);
uint16_t dbuToMv(const int16_t signalLevelDbu);

uint16_t mvPeakToMvRms(const uint16_t signalLevelMv);
uint16_t mvRmsToMvPeak(const uint16_t signalLevelMvRms);

#endif