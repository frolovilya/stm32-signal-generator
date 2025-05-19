#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../signals/Frequency.hpp"
#include "../signals/Level.hpp"
#include "../signals/WaveForm.hpp"
#include <cstdint>

struct Command {
  WaveForm waveForm;
  uint16_t frequencyHz;
  uint16_t levelMv;

  bool operator==(Command const &c) const {
    return waveForm == c.waveForm && frequencyHz == c.frequencyHz &&
           levelMv == c.levelMv;
  }
};

constexpr Command defaultCommand = {defaultWaveForm, defaultWaveFrequencyHz,
                                    defaultLevelMv};

std::ostream &operator<<(std::ostream &os, const Command &c);

#endif