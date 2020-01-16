#include "spi.h"

/*****************************************************/

void spi_init(void) {
  LPC_SYSCON->PRESETCTRL |= (1 << 0);        // Enable SSP
  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 11);    // Enable Clock SSP
  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 6);     // Enable Clock GPIO Ports
  LPC_SYSCON->SSP0CLKDIV = 0x01;             // CLKDIV SSP

  if ((LPC_SYSCON->SYSAHBCLKCTRL & (1 << 16)) != 1) {
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);    // Enable clock IOCON
    while ((LPC_SYSCON->SYSAHBCLKCTRL & (1 << 16)) == 1)
      ;
  }

  LPC_IOCON->PIO0_8 &= ~0x07;    // MISO pin function
  LPC_IOCON->PIO0_8 |= 0x01;
  LPC_IOCON->PIO0_9 &= ~0x07;    // MOSI pin function
  LPC_IOCON->PIO0_9 |= 0x01;
  LPC_IOCON->SCK_LOC = 0x01;    // SCK pin PIO2_11
  LPC_IOCON->PIO2_11 = 0x01;    // SCK pin function

  LPC_GPIO2->DIR |= (1 << 2);      // PI2_2 - Output, SS_PIN
  LPC_GPIO2->DATA &= ~(1 << 2);    // SS_PIN - LOW

  // SSP0CLKDIV = 1 -- F = (PCLK / (CPSDVSR X [SCR+1])) = (48,000,000 / (2 x [8 + 1])) = 1.0 MHz
  LPC_SSP0->CR0 = ((7 << 0)    // Data size - 8bit
      | (0 << 4)               // SPI frame
      | (0 << 6)               // CPOL
      | (0 << 7)               // CPHA
      | (23 << 8));            // Serial Clock Rate, PCLK / (CPSDVSR ? [SCR+1]).

  LPC_SSP0->CPSR = 2;    // CPSDIV

  LPC_SSP0->CR1 = ((0 << 0)    // 0 - Loop Back Mode Normal
      | (1 << 1)               // Enable ssp
      | (0 << 2));             // Master mode
}
/*****************************************************/
uint8_t Spi_transfer(uint8_t data) {
  while ((LPC_SSP0->SR & (SPP_SR_TNF | SPP_SR_BSY)) != SPP_SR_TNF)
    ;
  LPC_SSP0->DR = data;

  while ((LPC_SSP0->SR & (SPP_SR_BSY | SPP_SR_RNE)) != SPP_SR_RNE)
    ;
  return LPC_SSP0->DR;
}
/*****************************************************/