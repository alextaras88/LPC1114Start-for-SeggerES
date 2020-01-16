#include "LPC11xx.h"
#include "i2c.h"

#define EEPROM_ADDR 0x50

void eeprom_write_one(uint8_t addr, uint16_t addr_data, uint8_t data);
uint8_t eeprom_read_one(uint8_t addr, uint16_t addr_data);
void eeprom_write_buffer(uint8_t addr, uint16_t addr_data, uint8_t *buff, uint16_t len);
void eeprom_read_buffer(uint8_t addr, uint8_t addr_data, uint8_t* buff, uint16_t len);

