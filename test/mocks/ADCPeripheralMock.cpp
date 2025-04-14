#include "../../src/peripherals/ADCPeripheral.hpp"
#include <cstdint>

uint16_t ADCPeripheral::getVddaMV() { return 3300; }

ADC_TypeDef *ADCPeripheral::getPeripheral() const { return nullptr; };

void ADCPeripheral::configure() {}

ADCPeripheral adcInstance = ADCPeripheral();
