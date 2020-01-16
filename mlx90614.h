#include "LPC11xx.h"
#include "delay.h"
#include "i2c.h"

#define MLX90614_DEFAULT_ADDRESS 0x5A

#define MLX90614_REGISTER_TA 0x06
#define MLX90614_REGISTER_TOBJ1 0x07
#define MLX90614_REGISTER_TOBJ2 0x08
#define MLX90614_REGISTER_TOMAX 0x20
#define MLX90614_REGISTER_TOMIN 0x21
#define MLX90614_REGISTER_PWMCTRL 0x22
#define MLX90614_REGISTER_TARANGE 0x23
#define MLX90614_REGISTER_KE 0x24
#define MLX90614_REGISTER_CONFIG 0x25
#define MLX90614_REGISTER_ADDRESS 0x2E
#define MLX90614_REGISTER_ID0 0x3C
#define MLX90614_REGISTER_ID1 0x3D
#define MLX90614_REGISTER_ID2 0x3E
#define MLX90614_REGISTER_ID3 0x3F
#define MLX90614_REGISTER_SLEEP 0xFF // Not really a register, but close enough
/****************************************************/
uint8_t crc8(uint8_t inCrc, uint8_t inData);
uint8_t mlx90614_GetAddr(void);
//void mlx90614_SetAddr(uint8_t mlx_addr, uint8_t new_addr);
void mlx90614_WriteEEPROM(uint8_t mlx_addr, uint8_t reg, uint16_t data);
void mlx90614_i2c_write_data(uint8_t mlx_addr, uint8_t reg, uint16_t data);
uint16_t mlx90614_read_data(uint8_t mlx_addr, uint8_t reg);
uint16_t mlx90614_ReadObject(uint8_t mlx_addr);
uint16_t mlx90614_ReadObject2(uint8_t mlx_addr);
uint16_t mlx90614_ReadAmbient(uint8_t mlx_addr);
float mlx90614_GetTempAmbient(uint16_t value);
float mlx90614_GetTempObject(uint16_t value);