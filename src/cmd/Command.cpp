#include "Command.hpp"
#include <ostream>
#include <string>

std::ostream &operator<<(std::ostream &os, const Command &c) {
  os << waveFormToString(c.waveForm) << ", " << c.frequencyHz << "Hz, "
     << c.levelMV << "mV\n";

  return os;
}