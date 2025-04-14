#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <cstdint>
#include <string>

constexpr uint16_t minLevelMV = 200;
uint16_t getMaxLevelMV();
constexpr uint16_t defaultLevelMV = 1000;

uint16_t getPeakToPeakDigitalValue(uint16_t signalLevelMV);
uint16_t stringToLevelMV(const std::string str);

#endif