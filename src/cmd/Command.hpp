#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../signals/Frequency.hpp"
#include "../signals/Level.hpp"
#include "../signals/WaveForm.hpp"
#include <cstdint>

struct Command {
  WaveForm waveForm;
  uint16_t frequencyHz;
  uint16_t levelMV;

  bool operator==(Command const &c) const {
    return waveForm == c.waveForm && frequencyHz == c.frequencyHz &&
           levelMV == c.levelMV;
  }
};

std::ostream &operator<<(std::ostream &os, const Command &c);

#endif