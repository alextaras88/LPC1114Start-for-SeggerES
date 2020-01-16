#include "system.h"

/*****************************************************/
void clock_init(void) {
  uint32_t regVal;

  LPC_SYSCON->SYSPLLCLKSEL = 0x00000001; /* Select system OSC */
  LPC_SYSCON->SYSPLLCLKUEN = 0x01;       /* Update clock source */
  LPC_SYSCON->SYSPLLCLKUEN = 0x00;       /* toggle Update register once */
  LPC_SYSCON->SYSPLLCLKUEN = 0x01;
  while (!(LPC_SYSCON->SYSPLLCLKUEN & 0x01))
    ; /* Wait until updated */

  LPC_FLASHCTRL->FLASHCFG = 0x00000002;

  regVal = LPC_SYSCON->SYSPLLCTRL;
  regVal &= ~0x1FF;
  LPC_SYSCON->SYSPLLCTRL = (regVal | (0x00000001 << 5) | 0x00000003);

  /* Enable main system PLL, main system PLL bit 7 in PDRUNCFG. */
  LPC_SYSCON->PDRUNCFG &= ~(1 << 7);
  while (!(LPC_SYSCON->SYSPLLSTAT & 0x01))
    ; /* Wait until it's locked */

  LPC_SYSCON->MAINCLKSEL = 0x03; /* Select PLL clock output */
  LPC_SYSCON->MAINCLKUEN = 0x01; /* Update MCLK clock source */
  LPC_SYSCON->MAINCLKUEN = 0x00; /* Toggle update register once */
  LPC_SYSCON->MAINCLKUEN = 0x01;
  while (!(LPC_SYSCON->MAINCLKUEN & 0x01))
    ; /* Wait until updated */

  LPC_SYSCON->SYSAHBCLKDIV = 0x00000001; /* SYS AHB clock, typical is 1 or 2 or 4 */
}
/*****************************************************/
void clock_out(uint8_t div) {
  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);  // Enable Clock IOCON
  LPC_IOCON->PIO0_1 = 0xD1;                // Set PI0_1 to CLKOUT
  LPC_SYSCON->SYSAHBCLKCTRL &= ~(1 << 16); // Disable clock IOCON
  LPC_SYSCON->CLKOUTDIV = (uint32_t)div;   // Set CLKOUT_DIV
  LPC_SYSCON->CLKOUTCLKSEL = 0X00000003;   // CLKOUT clock source - Main clock
  LPC_SYSCON->CLKOUTUEN = 0;
  LPC_SYSCON->CLKOUTUEN = 1;
  while (!(LPC_SYSCON->CLKOUTUEN & 0x01))
    ; // Wait until updated
}
/*****************************************************/