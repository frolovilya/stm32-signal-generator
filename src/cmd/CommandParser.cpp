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
  return stringFormat("Expecting three arguments: WaveForm Frequency Level\n"
                      "Where WaveForm: sine|square|saw|triangle; Frequency, "
                      "Hz: %d..%d; Level, mV: %d..%d\n"
                      "Example: sine 440 1000",
                      minWaveFrequencyHz, maxWaveFrequencyHz, minLevelMV,
                      getMaxLevelMV());
}

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
  uint16_t level = stringToLevelMV(splitString[2]);

  return {waveForm, frequency, level};
}