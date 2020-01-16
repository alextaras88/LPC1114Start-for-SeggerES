#include "timer.h"

/*****************************************************/
void timer_16_0_init(void) {

  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 7); //enable timer clock
  LPC_TMR16B0->PR = 48000;               //prescaler 48000 = 1000ms
  LPC_TMR16B0->MCR = 0x03;               //interrupt and reset counter match1
  LPC_TMR16B0->CCR = 0;                  //timer mode
  LPC_TMR16B0->MR0 = 500;                //set match1 time in 1000/500 = 2Hz
  NVIC_EnableIRQ(TIMER_16_0_IRQn);       //enable interrupt
  LPC_TMR16B0->TCR = 1;                  //start timer
}
/*****************************************************/
void CT16B0_IRQHandler(void) {
  if (LPC_TMR16B0->IR & (1 << 0)) {

    LPC_TMR16B0->IR = (1 << 0); //reset flag

    LPC_GPIO2->DATA ^= (1 << 6);
  }
  if (LPC_TMR16B0->IR & (1 << 1)) {

    LPC_TMR16B0->IR = (1 << 1); //reset flag
  }
  if (LPC_TMR16B0->IR & (1 << 2)) {

    LPC_TMR16B0->IR = (1 << 2); //reset flag
  }
  if (LPC_TMR16B0->IR & (1 << 3)) {

    LPC_TMR16B0->IR = (1 << 3); //reset flag
  }
}
/*****************************************************/
void timer_16_1_init(void) {

  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 8); //enable timer clock

  if ((LPC_SYSCON->SYSAHBCLKCTRL & (1 << 16)) != 1) {
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16); // Enable clock IOCON
    while ((LPC_SYSCON->SYSAHBCLKCTRL & (1 << 16)) == 1)
      ;
  }

  LPC_IOCON->PIO1_8 &= ~0x2F; // CAP0 pin function
  LPC_IOCON->PIO1_8 |= 0x01;  // Pull up resistor

 
  LPC_TMR16B1->CCR |= 0x05;            //timer mode
  LPC_TMR16B1->CTCR |=0x00;
  LPC_TMR16B1->PR = 48-1;
 
  
  NVIC_EnableIRQ(TIMER_16_1_IRQn); //enable interrupt
  LPC_TMR16B1->TCR = 1;            //start timer
}

void CT16B1_IRQHandler(void) {
  if (LPC_TMR16B1->IR & (1 << 0)) {

    LPC_TMR16B1->IR = (1 << 0); //reset flag
  }
  if (LPC_TMR16B1->IR & (1 << 1)) {

    LPC_TMR16B1->IR = (1 << 1); //reset flag
  }
  if (LPC_TMR16B1->IR & (1 << 2)) {

    LPC_TMR16B1->IR = (1 << 2); //reset flag
  }
  if (LPC_TMR16B1->IR & (1 << 3)) {

    LPC_TMR16B1->IR = (1 << 3); //reset flag
  }
  if (LPC_TMR16B1->IR & (1 << 4)) {

   
    LPC_TMR16B1->IR = (1 << 4); //reset flag
  }
}
