#ifndef UARTPERIPHERAL_HPP
#define UARTPERIPHERAL_HPP

#include "../sys/stm32f446xxTypes.hpp"
#include "Peripheral.hpp"
#include <cstdlib>
#include <functional>
#include <string>

using UART_RX_Handler = void(std::string str);

class UARTPeripheral : public Peripheral<USART_TypeDef> {
public:
  void configure() override;
  void start();
  void send(std::string_view data);
  void receive(std::function<UART_RX_Handler> callback);
  void handleInterrupt();

private:
  virtual void configureGPIO() = 0;
  virtual void configureRCC() = 0;
  virtual void configureNVIC() = 0;

  std::function<UART_RX_Handler> rxCallback;
  static constexpr int rxBufferSize = 100;
  int rxBufferIndex = 0;
  char rxBuffer[rxBufferSize];
};

#endif