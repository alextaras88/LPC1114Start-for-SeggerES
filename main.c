#include "main.h"

uint8_t buffer_rx[10];
char str[40];
uint32_t status = 0;
uint8_t data;
uint8_t buff[6] = {0x09, 0x02, 0x03, 0xAA, 0x05, 0x88};
uint8_t buff_rx_eeptom[64];

uint8_t w = 0;
float temp_o, temp_a;

/*****************************************************/
void exti_gpio(void);
/*****************************************************/

void GPIO0_IRQHandler(void) {
  if (LPC_GPIO0->MIS & (1 << 3)) {
    LPC_GPIO0->IC |= (1 << 3);    // clear interrupt for pin
    status++;
  }
}

int main(void) {
  clock_init();
  delay_init();
  //  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 6);
  //  LPC_GPIO2->DIR |= (1 << 6);
  // timer_16_0_init();
  // timer_16_1_init();

  // clock_out(32);
  // spi_init();
  i2c_init();
  Delay_ms(200);
  ssd1306_Init();
  exti_gpio();
  ssd1306_SetCursor(0, 0);
  ssd1306_WriteString("lpcq1114 - ssd1306", Font_7x10, White);
  ssd1306_UpdateScreen();

  // ssd1306_Fill(White);

  // data = mlx90614_GetAddr();
  // sprintf(str,"0x%X\r\n" ,data);
  // printf(str);
  // eeprom_write_buffer(EEPROM_ADDR, 64, buff, 6);
  // eeprom_write_one(EEPROM_ADDR, 0, 0xA7);
  // Delay_ms(500);
  // data = eeprom_read_one(EEPROM_ADDR, 0);
  // eeprom_read_buffer(EEPROM_ADDR, 64, buff_rx_eeptom, 6);
  //  sprintf(str, "0x%X "
  //               "0x%X "
  //               "0x%X "
  //               "0x%X "
  //               "0x%X "
  //               "0x%X\r\n",
  //      buff_rx_eeptom[0], buff_rx_eeptom[1], buff_rx_eeptom[2], buff_rx_eeptom[3], buff_rx_eeptom[4],
  //      buff_rx_eeptom[5]);
  //  printf(str);
  // uart_init(9600);

  while (1) {
    sprintf(str, "%d", status);
    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(str, Font_11x18, White);
    ssd1306_UpdateScreen();

    //    temp_a = mlx90614_GetTempAmbient(mlx90614_ReadAmbient(MLX90614_DEFAULT_ADDRESS));
    //    temp_o = mlx90614_GetTempObject(mlx90614_ReadObject(MLX90614_DEFAULT_ADDRESS));
    //    sprintf(str,"Ambient:%.2f  " "Object:%.2f\r\n", temp_a, temp_o);
    //    printf(str);
    //    Delay_ms(100);

    //    Delay_ms(200);
    //
    //    SPI_CS_LOW;
    //    buffer_rx[0] = Spi_transfer(0xAA);
    //    buffer_rx[1] = Spi_transfer(0x66);
    //    buffer_rx[2] = Spi_transfer(0xFD);
    //    buffer_rx[3] = Spi_transfer(0xDE);
    //    SPI_CS_HIGH;
    //   // uart_send_buffer(buffer_rx, 4);
    //    sprintf(str, "0x%X "
    //                 "0x%X "
    //                 "0x%X "
    //                 "0x%X\r\n",
    //        buffer_rx[0], buffer_rx[1], buffer_rx[2], buffer_rx[3]);
    //    printf(str);
    //    Delay_ms(500);
  }
}

void exti_gpio(void) {
  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 6);
  LPC_GPIO0->DIR &= ~(1 << 3);

  LPC_GPIO0->IS |= (1 << 3);
  LPC_GPIO0->IEV &= ~(1 << 3);
  LPC_GPIO0->IE |= (1 << 3);
  NVIC_EnableIRQ(EINT0_IRQn);
}