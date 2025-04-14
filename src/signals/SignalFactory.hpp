#ifndef WAVEFACTORY_HPP
#define WAVEFACTORY_HPP

#include "Frequency.hpp"
#include "Level.hpp"
#include "WaveForm.hpp"
#include "Welle.hpp"
#include <string>
#include <vector>

/**
 * Return a vector containing a single period of a generated signal
 *
 * @param waveForm wave form of a signal
 * @param frequencyHz wave frequency in Hz
 * @param signalLevelMV signal level in mV with 0 DC offset
 */
template <typename T>
std::vector<T> generateSignalPeriod(const WaveForm waveForm,
                                    const uint16_t frequencyHz,
                                    const uint16_t signalLevelMV) {

  const int samplingRate = getSamplingRateHz();
  const uint16_t peakToPeak = getPeakToPeakDigitalValue(signalLevelMV);
  const double phaseShift = 0;

  switch (waveForm) {
  case WaveForm::SQUARE:
    return welle::SquareWave<T>(samplingRate)
        .generatePeriod(frequencyHz, peakToPeak, phaseShift);
  case WaveForm::SAW:
    return welle::SawWave<T>(samplingRate)
        .generatePeriod(frequencyHz, peakToPeak, phaseShift);
  case WaveForm::TRIANGLE:
    return welle::TriangleWave<T>(samplingRate)
        .generatePeriod(frequencyHz, peakToPeak, phaseShift);
  case WaveForm::SINE:
  default:
    return welle::SineWave<T>(samplingRate)
        .generatePeriod(frequencyHz, peakToPeak, phaseShift);
  }
}

#endif