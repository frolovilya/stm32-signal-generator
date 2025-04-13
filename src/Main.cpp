#include "cmd/CommandParser.hpp"
#include "peripherals/Peripherals.hpp"
#include "signals/Frequency.hpp"
#include "signals/Level.hpp"
#include "signals/SignalFactory.hpp"
#include "signals/WaveForm.hpp"
#include <iostream>
#include <string>

using namespace std;

// Samples buffer
vector<uint16_t> samples;

void printCurrentSignalInfo(WaveForm waveForm, uint16_t frequency,
                            uint16_t level) {
  cout << "Generating " << waveFormToString(waveForm) << " " << frequency
       << "Hz "
       << " " << level << "mV"
       << " signal\n";
}

void stream(WaveForm waveForm, uint16_t frequency, uint16_t level) {
  samples = generateSignalPeriod<uint16_t>(waveForm, frequency, level);
  printCurrentSignalInfo(waveForm, frequency, level);

  dacInstance.start(samples.data(), samples.size());
}

void parseAndApplyCommand(std::string str) {
  const auto command = tryParseCommand(str);
  stream(command.waveForm, command.frequencyHz, command.levelMV);
}

UARTPeripheral *getUARTPeripheral() {
#ifdef USE_USART3
  return &uart3Instance;
#else
  return &uart2Instance;
#endif
}

int main() {
  rccInstance.configure();

  auto uart = getUARTPeripheral();
  uart->configure();
  uart->start();
  uart->receive(&parseAndApplyCommand);

  dacInstance.configure();

  adcInstance.configure();

  stream(defaultWaveForm, defaultWaveFrequencyHz, defaultLevelMV);

  while (1) {
  }

  return 0;
}