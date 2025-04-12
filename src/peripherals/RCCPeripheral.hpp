#ifndef RCCPERIPHERAL_HPP
#define RCCPERIPHERAL_HPP

#include "../sys/stm32f446xxTypes.hpp"
#include "Peripheral.hpp"

class RCCPeripheral : public Peripheral<RCC_TypeDef> {
public:
  void configure() override;
  RCC_TypeDef *getPeripheral() const override;
};

#endif