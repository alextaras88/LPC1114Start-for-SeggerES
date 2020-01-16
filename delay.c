#include "delay.h"

volatile uint32_t msTicks;

void delay_init(void) {
  SysTick->LOAD = TimerTick;
  SysTick->VAL  = TimerTick;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}
/*****************************************************/
void Delay_ms(uint32_t dlyTicks) {
  uint32_t curTicks;
  curTicks = msTicks;

  while ((msTicks - curTicks) < dlyTicks)
    ;
}
/*****************************************************/
void SysTick_Handler(void) {
  msTicks++;
}
/*****************************************************/