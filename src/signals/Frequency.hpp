#ifndef FREQUENCY_HPP
#define FREQUENCY_HPP

#include <cstdint>
#include <string>

constexpr uint16_t minWaveFrequencyHz = 20;
constexpr uint16_t maxWaveFrequencyHz = 20000;
constexpr uint16_t defaultWaveFrequencyHz = 440;

uint32_t getSamplingRateHz();
uint16_t stringToFrequencyHz(const std::string str);

#endif