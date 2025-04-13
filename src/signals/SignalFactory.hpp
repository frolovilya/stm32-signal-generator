#ifndef WAVEFACTORY_HPP
#define WAVEFACTORY_HPP

#include "Frequency.hpp"
#include "Level.hpp"
#include "WaveForm.hpp"
#include "Welle.hpp"
#include <string>
#include <vector>

template <typename T>
std::vector<T> generateSignalPeriod(const WaveForm waveForm,
                                    const uint16_t frequency,
                                    const uint16_t signalLevelMV) {

  const int samplingRate = getSamplingRateHz();
  const uint16_t peakToPeak = getPeakToPeakDigitalValue(signalLevelMV);
  const double phaseShift = 0;

  switch (waveForm) {
  case WaveForm::SQUARE:
    return welle::SquareWave<T>(samplingRate)
        .generatePeriod(frequency, peakToPeak, phaseShift);
  case WaveForm::SAW:
    return welle::SawWave<T>(samplingRate)
        .generatePeriod(frequency, peakToPeak, phaseShift);
  case WaveForm::TRIANGLE:
    return welle::TriangleWave<T>(samplingRate)
        .generatePeriod(frequency, peakToPeak, phaseShift);
  case WaveForm::SINE:
  default:
    return welle::SineWave<T>(samplingRate)
        .generatePeriod(frequency, peakToPeak, phaseShift);
  }
}

#endif