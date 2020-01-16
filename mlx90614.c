#include "mlx90614.h"

/************************************************************************************/
/* MLX90614 family				                                    */
/* Single and Dual Zone
 */
/* Infra Red Thermometer in TO-39
 */
/************************************************************************************/
extern volatile uint32_t I2CCount;
extern volatile uint8_t I2CMasterBuffer[BUFSIZE];
extern volatile uint8_t I2CSlaveBuffer[BUFSIZE];
extern volatile uint32_t I2CMasterState;
extern volatile uint32_t I2CReadLength, I2CWriteLength;
/************************************************************************************/
uint8_t crc8(uint8_t inCrc, uint8_t inData) {
  uint8_t i;
  uint8_t data;
  data = inCrc ^ inData;
  for (i = 0; i < 8; i++) {
    if ((data & 0x80) != 0) {
      data <<= 1;
      data ^= 0x07;
    } else {
      data <<= 1;
    }
  }

  return data;
}
/************************************************************************************/
uint8_t mlx90614_GetAddr(void) {
  uint16_t addr;

  addr = mlx90614_read_data(MLX90614_DEFAULT_ADDRESS, MLX90614_REGISTER_ADDRESS);

  return (uint8_t)addr;
}
/************************************************************************************/
// void mlx90614_SetAddr(uint8_t mlx_addr, uint8_t new_addr){
//
//	uint16_t set_addr;
//
//	set_addr = mlx90614_read_data(MLX90614_DEFAULT_ADDRESS, MLX90614_REGISTER_ADDRESS);
//	set_addr &= 0xFF00;
//	set_addr |= new_addr;
//
//	mlx90614_WriteEEPROM(mlx_addr, MLX90614_REGISTER_ADDRESS, set_addr);

//}
/************************************************************************************/
void mlx90614_WriteEEPROM(uint8_t mlx_addr, uint8_t reg, uint16_t data) {
  mlx90614_i2c_write_data(mlx_addr, reg, data);
  Delay_ms(5);
}
/************************************************************************************/
void mlx90614_i2c_write_data(uint8_t mlx_addr, uint8_t reg, uint16_t data) {
  uint16_t i;

  uint8_t crc;
  uint8_t lsb = data & 0x00FF;
  uint8_t msb = (data >> 8);

  for (i = 0; i < BUFSIZE; i++) /* clear buffer */
  {
    I2CMasterBuffer[i] = 0;
    I2CSlaveBuffer[i]  = 0;
  }

  crc = crc8(0, (mlx_addr << 1));
  crc = crc8(crc, reg);
  crc = crc8(crc, lsb);
  crc = crc8(crc, msb);

  I2CWriteLength     = 4;
  I2CReadLength      = 0;
  I2CMasterBuffer[0] = (mlx_addr << 1) + 0;
  I2CMasterBuffer[1] = reg;
  I2CMasterBuffer[2] = lsb;
  I2CMasterBuffer[3] = msb;
  I2CEngine();

  //  Start_i2c(I2C1);
  //  Write_addr_i2c(I2C1, mlx_addr, 0);
  //  Write_data_i2c(I2C1, reg);
  //  Write_data_i2c(I2C1, lsb);
  //  Write_last_data_i2c(I2C1, msb);
  //  Stop_i2c(I2C1);
}
/************************************************************************************/
uint16_t mlx90614_read_data(uint8_t mlx_addr, uint8_t reg) {
  uint16_t i;

  uint16_t value = 0;
  uint8_t lsb, msb, pec, crc;

  for (i = 0; i < BUFSIZE; i++) /* clear buffer */
  {
    I2CMasterBuffer[i] = 0;
    I2CSlaveBuffer[i]  = 0;
  }

  I2CWriteLength = 2;
  I2CReadLength  = 3;

  I2CMasterBuffer[0] = (mlx_addr << 1) + 0;
  I2CMasterBuffer[1] = reg;
  I2CMasterBuffer[2] = (mlx_addr << 1) + 1;
  I2CEngine();

  crc = crc8(0, (mlx_addr << 1));
  crc = crc8(crc, reg);
  crc = crc8(crc, (mlx_addr << 1) + 1);
  crc = crc8(crc, I2CSlaveBuffer[0]);
  crc = crc8(crc, I2CSlaveBuffer[1]);

  if (crc == I2CSlaveBuffer[2]) {
    value = (I2CSlaveBuffer[1] << 8) | I2CSlaveBuffer[0];
    return value;
  } else {
    return 0;
  }
}
/************************************************************************************/
uint16_t mlx90614_ReadObject(uint8_t mlx_addr) {
  return mlx90614_read_data(mlx_addr, MLX90614_REGISTER_TOBJ1);
}
/************************************************************************************/
uint16_t mlx90614_ReadObject2(uint8_t mlx_addr) {
  return mlx90614_read_data(mlx_addr, MLX90614_REGISTER_TOBJ2);
}
/************************************************************************************/
uint16_t mlx90614_ReadAmbient(uint8_t mlx_addr) {
  return mlx90614_read_data(mlx_addr, MLX90614_REGISTER_TA);
}
/************************************************************************************/
float mlx90614_GetTempAmbient(uint16_t value) {
  float temp = 0;

  temp = (float)value * 0.02;
  temp -= 273.15;
  temp = temp * 9.0 / 5.0 + 32;
  temp = 5.0 / 9.0 * (temp - 32);

  return temp;
}
/************************************************************************************/
float mlx90614_GetTempObject(uint16_t value) {
  float temp = 0;

  temp = (float)value * 0.02;
  temp -= 273.15;
  temp = temp * 9.0 / 5.0 + 32;
  temp = 5.0 / 9.0 * (temp - 32);

  return temp;
}
/************************************************************************************/
/*****************************************************/