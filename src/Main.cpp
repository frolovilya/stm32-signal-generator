#include "cmd/CommandParser.hpp"
#include "cmd/Command.hpp"
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

void printCurrentSignalInfo(const Command &cmd) {
  cout << "Generating " << cmd << " signal\n";
}

void stream(const Command &cmd) {
  samples = generateSignalPeriod<uint16_t>(cmd.waveForm, cmd.frequencyHz,
                                           cmd.levelMv);
  printCurrentSignalInfo(cmd);

  dacInstance.start(samples.data(), samples.size());
}

void parseAndApplyCommand(std::string str) {
  try {
    const auto command = parseCommand(str);
    stream(command);
  } catch (const std::exception &e) {
    cout << e.what() << "\n";
  }
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

  stream(defaultCommand);

  while (1) {
  }

  return 0;
}