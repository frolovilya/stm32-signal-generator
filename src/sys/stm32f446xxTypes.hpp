#ifndef STM32TYPES_HPP
#define STM32TYPES_HPP

#ifdef EMBEDDED
extern "C" {
#include <stm32f446xx.h>
}
#else

struct DAC_TypeDef {};
struct ADC_TypeDef {};
struct RCC_TypeDef {};
struct USART_TypeDef {};

#endif

#endif