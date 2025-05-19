#include "CommandParser.hpp"
#include "../shared/StringFormat.hpp"
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

std::string getUsageHelp() {
  return "Usage: {sine|square|saw|triangle} frequency[Hz] "
         "level{[mV]|mVRMS|dBV|dBu}\n"
         "Example: sine 440hz -10dbv";
}

/**
 * Parse received string command into WaveForm, Frequency, Level
 */
Command parseCommand(const std::string str) {
  std::istringstream iss(str);
  std::string item;
  std::vector<std::string> splitString;
  while (std::getline(iss, item, ' ')) {
    std::back_inserter(splitString) = item;
  }

  if (splitString.size() != 3) {
    throw std::invalid_argument(getUsageHelp());
  }

  WaveForm waveForm = stringToWaveForm(splitString[0]);
  uint16_t frequency = stringToFrequencyHz(splitString[1]);
  uint16_t level = stringToLevelMv(splitString[2]);

  return {waveForm, frequency, level};
}