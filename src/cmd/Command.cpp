#include "Command.hpp"
#include <ostream>
#include <string>

std::ostream &operator<<(std::ostream &os, const Command &c) {
  os << waveFormToString(c.waveForm) << ", " << c.frequencyHz << "Hz, "
     << mvPeakToMvRms(c.levelMv) << "mV RMS (" << mvToDbv(c.levelMv) << "dBV)";

  return os;
}