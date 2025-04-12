#ifndef COMMANDPARSER_HPP
#define COMMANDPARSER_HPP

#include "../signals/Frequency.hpp"
#include "../signals/Level.hpp"
#include "../signals/WaveForm.hpp"
#include <cstdint>

void printUsageHelp();
std::tuple<WaveForm, uint16_t, uint16_t> tryParseCommand(std::string str);

#endif