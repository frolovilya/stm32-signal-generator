#include "CommandParser.hpp"
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

void printUsageHelp() {
  cout << "Usage: sine|square|saw|triangle [" << minWaveFrequencyHz << ".."
       << maxWaveFrequencyHz << "](Hz) [" << minLevelMV << ".." << getMaxLevelMV()
       << "](mV)\n";
}

Command parseCommand(const std::string str) {
  std::istringstream iss(str);
  std::string item;
  std::vector<std::string> splitString;
  while (std::getline(iss, item, ' ')) {
    std::back_inserter(splitString) = item;
  }

  if (splitString.size() != 3) {
    throw std::invalid_argument(
        "Expecting three input parameters: wave, frequency, level");
  }

  WaveForm waveForm = stringToWaveForm(splitString[0]);
  uint16_t frequency = stringToFrequencyHz(splitString[1]);
  uint16_t level = stringToLevelMV(splitString[2]);

  return {waveForm, frequency, level};
}

constexpr Command defaultCommand() {
  return {defaultWaveForm, defaultWaveFrequencyHz, defaultLevelMV};
}

Command tryParseCommand(const std::string str) {
  try {
    return parseCommand(str);
  } catch (const std::exception &e) {
    cout << e.what() << "\n";
    printUsageHelp();

    return defaultCommand();
  }
}