#include "eeprom.h"

extern volatile uint32_t I2CCount;
extern volatile uint8_t I2CMasterBuffer[BUFSIZE];
extern volatile uint8_t I2CSlaveBuffer[BUFSIZE];
extern volatile uint32_t I2CMasterState;
extern volatile uint32_t I2CReadLength, I2CWriteLength;
/****************************************************/
void eeprom_write_one(uint8_t addr, uint16_t addr_data, uint8_t data) {
  uint16_t i;

  for (i = 0; i < BUFSIZE; i++) /* clear buffer */
  {
    I2CMasterBuffer[i] = 0;
    I2CSlaveBuffer[i]  = 0;
  }

  I2CWriteLength     = 4;
  I2CReadLength      = 0;
  I2CMasterBuffer[0] = (addr << 1) + 0;
  I2CMasterBuffer[1] = (uint8_t)(addr_data >> 8);
  I2CMasterBuffer[2] = (uint8_t)addr_data;
  I2CMasterBuffer[3] = data;
  I2CEngine();
}
/****************************************************/
uint8_t eeprom_read_one(uint8_t addr, uint16_t addr_data) {
  uint16_t i;

  for (i = 0; i < BUFSIZE; i++) /* clear buffer */
  {
    I2CMasterBuffer[i] = 0;
    I2CSlaveBuffer[i]  = 0;
  }

  I2CWriteLength     = 3;
  I2CReadLength      = 0;
  I2CMasterBuffer[0] = (addr << 1) + 0;
  I2CMasterBuffer[1] = (uint8_t)(addr_data >> 8);
  I2CMasterBuffer[2] = (uint8_t)addr_data;
  I2CEngine();
  I2CWriteLength     = 1;
  I2CReadLength      = 1;
  I2CMasterBuffer[0] = (addr << 1) + 1;
  I2CEngine();
  return I2CSlaveBuffer[0];
}
/****************************************************/
void eeprom_write_buffer(uint8_t addr, uint16_t addr_data, uint8_t *buff, uint16_t len) {
  uint16_t i, d = 3;

  for (i = 0; i < BUFSIZE; i++) /* clear buffer */
  {
    I2CMasterBuffer[i] = 0;
    I2CSlaveBuffer[i]  = 0;
  }

  I2CWriteLength     = len + 3;
  I2CReadLength      = 0;
  I2CMasterBuffer[0] = (addr << 1) + 0;
  I2CMasterBuffer[1] = (uint8_t)(addr_data >> 8);
  I2CMasterBuffer[2] = (uint8_t)addr_data;
  for (i = 0; i < len; i++) {
    I2CMasterBuffer[d] = buff[i];
    d++;
  }

  I2CEngine();
}
/****************************************************/
void eeprom_read_buffer(uint8_t addr, uint8_t addr_data, uint8_t *buff, uint16_t len) {
  uint16_t i;

  for (i = 0; i < BUFSIZE; i++) /* clear buffer */
  {
    I2CMasterBuffer[i] = 0;
    I2CSlaveBuffer[i]  = 0;
  }

  I2CWriteLength     = 3;
  I2CReadLength      = 0;
  I2CMasterBuffer[0] = (addr << 1) + 0;
  I2CMasterBuffer[1] = (uint8_t)(addr_data >> 8);
  I2CMasterBuffer[2] = (uint8_t)addr_data;
  I2CEngine();
  I2CWriteLength     = 1;
  I2CReadLength      = len;
  I2CMasterBuffer[0] = (addr << 1) + 1;
  I2CEngine();
  for (i = 0; i < len; i++) /* clear buffer */
  {
    buff[i] = I2CSlaveBuffer[i];
  }
}
/****************************************************/