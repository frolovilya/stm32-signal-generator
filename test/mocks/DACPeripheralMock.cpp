#include "../../src/peripherals/DACPeripheral.hpp"
#include <cstdint>

uint32_t DACPeripheral::getFrequency() const { return 1000000; }
DAC_TypeDef *DACPeripheral::getPeripheral() const { return nullptr; };

void DACPeripheral::configure() {}

DACPeripheral dacInstance = DACPeripheral();
