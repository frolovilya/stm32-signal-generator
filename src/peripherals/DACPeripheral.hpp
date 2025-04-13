#ifndef DACPERIPHERAL_HPP
#define DACPERIPHERAL_HPP

#include "../sys/stm32f446xxTypes.hpp"
#include "Peripheral.hpp"
#include <cstdint>

class DACPeripheral : public Peripheral<DAC_TypeDef> {
public:
  void configure() override;
  void start(uint16_t *dacBuffer, int dataLength);
  DAC_TypeDef *getPeripheral() const override;
  uint32_t getFrequency() const;
  uint16_t getMaxDigitalValue() const;

private:
  void configureGPIOA();
  void configureDMA();
  void configureTimer();
};

#endif