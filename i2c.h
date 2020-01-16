#include "LPC11xx.h"

/*****************************************************/
#define BUFSIZE 128
#define MAX_TIMEOUT 0x00FFFFFF

#define READ_WRITE 0x01

/* For more info, read NXP's SE95 datasheet */

#define RD_BIT 0x01

#define I2C_IDLE 0
#define I2C_STARTED 1
#define I2C_RESTARTED 2
#define I2C_REPEATED_START 3
#define DATA_ACK 4
#define DATA_NACK 5
#define I2C_BUSY 6
#define I2C_NO_DATA 7
#define I2C_NACK_ON_ADDRESS 8
#define I2C_NACK_ON_DATA 9
#define I2C_ARBITRATION_LOST 10
#define I2C_TIME_OUT 11
#define I2C_OK 12

#define I2CSTATE_IDLE       0x000
#define I2CSTATE_PENDING    0x001
#define I2CSTATE_ACK        0x101
#define I2CSTATE_NACK       0x102
#define I2CSTATE_SLA_NACK   0x103
#define I2CSTATE_ARB_LOSS   0x104

#define I2CONSET_I2EN (0x1 << 6) /* I2C Control Set Register */
#define I2CONSET_AA (0x1 << 2)
#define I2CONSET_SI (0x1 << 3)
#define I2CONSET_STO (0x1 << 4)
#define I2CONSET_STA (0x1 << 5)

#define I2CONCLR_AAC (0x1 << 2) /* I2C Control clear Register */
#define I2CONCLR_SIC (0x1 << 3)
#define I2CONCLR_STAC (0x1 << 5)
#define I2CONCLR_I2ENC (0x1 << 6)

#define I2DAT_I2C 0x00000000 /* I2C Data Reg */
#define I2ADR_I2C 0x00000000 /* I2C Slave Address Reg */

/*****************************************************/
extern void I2C_IRQHandler(void);
void i2c_init(void);
uint32_t i2c_start(void);
uint32_t i2c_stop(void);
uint32_t I2CEngine(void);
/*****************************************************/