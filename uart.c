#include "uart.h"

void uart_init(uint32_t br) {
  uint32_t Fdiv;
  uint32_t regVal;

  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 12);
  LPC_SYSCON->UARTCLKDIV = 0x1;

  if ((LPC_SYSCON->SYSAHBCLKCTRL & (1 << 16)) != 1) {
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16); // Enable clock IOCON
    while ((LPC_SYSCON->SYSAHBCLKCTRL & (1 << 16)) == 1)
      ;
  }

  LPC_IOCON->PIO1_6 &= ~0x07;
  LPC_IOCON->PIO1_6 |= 0x01; // UART RXD
  LPC_IOCON->PIO1_7 &= ~0x07;
  LPC_IOCON->PIO1_7 |= 0x01; // UART TXD

  LPC_UART->LCR = (3 << 0) | (0 << 2) | (0 << 3) | (1 << 7);

  regVal = LPC_SYSCON->UARTCLKDIV;
  Fdiv = (((SystemCoreClock / LPC_SYSCON->SYSAHBCLKDIV) / regVal) / 16) / br;

  LPC_UART->DLM = Fdiv / 256;
  LPC_UART->DLL = Fdiv % 256;
  LPC_UART->LCR = 0x03;
  LPC_UART->FCR = (1 << 0) | (1 << 1) | (1 << 2) | (0 << 6);

  regVal = LPC_UART->LSR;
}
/*****************************************************/
void uart_send(char c) {
  while (!(LPC_UART->LSR & LSR_THRE))
    ;
  LPC_UART->THR = c;
}
/*****************************************************/
void uart_send_string(char *str) {
  uint8_t i = 0;

  while (str[i])
    ;
  uart_send(str[i++]);
}
/*****************************************************/
void uart_send_buffer(uint8_t *buff, uint16_t len) {
  uint16_t i;

  for (i = 0; i < len; i++) {
    while (!(LPC_UART->LSR & LSR_THRE))
      ;
    LPC_UART->THR = buff[i];
  }
}
/*****************************************************/