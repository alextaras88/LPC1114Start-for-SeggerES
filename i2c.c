#include "i2c.h"

volatile uint32_t I2CMasterState = I2C_IDLE;
volatile uint32_t I2CSlaveState  = I2C_IDLE;
volatile uint32_t timeout        = 0;

volatile uint32_t I2CMode;

volatile uint8_t I2CMasterBuffer[BUFSIZE];
volatile uint8_t I2CSlaveBuffer[BUFSIZE];
volatile uint32_t I2CCount = 0;
volatile uint32_t I2CReadLength;
volatile uint32_t I2CWriteLength;

volatile uint32_t RdIndex = 0;
volatile uint32_t WrIndex = 0;

/*****************************************************/
void I2C_IRQHandler(void) {
  uint8_t StatValue;

  timeout = 0;
  /* this handler deals with master read and master write only */
  StatValue = LPC_I2C->STAT;
  switch (StatValue) {
  case 0x08: /* A Start condition is issued. */
    WrIndex         = 0;
    RdIndex         = 0;
    LPC_I2C->DAT    = I2CMasterBuffer[WrIndex++];
    LPC_I2C->CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
    break;

  case 0x10: /* A repeated started is issued */
    RdIndex = 0;
    /* Send SLA with R bit set, */
    LPC_I2C->DAT    = I2CMasterBuffer[WrIndex++];
    LPC_I2C->CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
    break;

  case 0x18: /* Regardless, it's a ACK */
    if (I2CWriteLength == 1) {
      LPC_I2C->CONSET = I2CONSET_STO; /* Set Stop flag */
      I2CMasterState  = I2C_NO_DATA;
    } else {
      LPC_I2C->DAT = I2CMasterBuffer[WrIndex++];
    }
    LPC_I2C->CONCLR = I2CONCLR_SIC;
    break;

  case 0x28: /* Data byte has been transmitted, regardless ACK or NACK */
    if (WrIndex < I2CWriteLength) {
      LPC_I2C->DAT = I2CMasterBuffer[WrIndex++]; /* this should be the last one */
    } else {
      if (I2CReadLength != 0) {
        LPC_I2C->CONSET = I2CONSET_STA; /* Set Repeated-start flag */
      } else {
        LPC_I2C->CONSET = I2CONSET_STO; /* Set Stop flag */
        I2CMasterState  = I2C_OK;
      }
    }
    LPC_I2C->CONCLR = I2CONCLR_SIC;
    break;

  case 0x30:
    LPC_I2C->CONSET = I2CONSET_STO; /* Set Stop flag */
    I2CMasterState  = I2C_NACK_ON_DATA;
    LPC_I2C->CONCLR = I2CONCLR_SIC;
    break;

  case 0x40: /* Master Receive, SLA_R has been sent */
    if ((RdIndex + 1) < I2CReadLength) {
      /* Will go to State 0x50 */
      LPC_I2C->CONSET = I2CONSET_AA; /* assert ACK after data is received */
    } else {
      /* Will go to State 0x58 */
      LPC_I2C->CONCLR = I2CONCLR_AAC; /* assert NACK after data is received */
    }
    LPC_I2C->CONCLR = I2CONCLR_SIC;
    break;

  case 0x50: /* Data byte has been received, regardless following ACK or NACK */
    I2CSlaveBuffer[RdIndex++] = LPC_I2C->DAT;
    if ((RdIndex + 1) < I2CReadLength) {
      LPC_I2C->CONSET = I2CONSET_AA; /* assert ACK after data is received */
    } else {
      LPC_I2C->CONCLR = I2CONCLR_AAC; /* assert NACK on last byte */
    }
    LPC_I2C->CONCLR = I2CONCLR_SIC;
    break;

  case 0x58:
    I2CSlaveBuffer[RdIndex++] = LPC_I2C->DAT;
    I2CMasterState            = I2C_OK;
    LPC_I2C->CONSET           = I2CONSET_STO; /* Set Stop flag */
    LPC_I2C->CONCLR           = I2CONCLR_SIC; /* Clear SI flag */
    break;

  case 0x20: /* regardless, it's a NACK */
  case 0x48:
    LPC_I2C->CONSET = I2CONSET_STO; /* Set Stop flag */
    I2CMasterState  = I2C_NACK_ON_ADDRESS;
    LPC_I2C->CONCLR = I2CONCLR_SIC;
    break;

  case 0x38: /* Arbitration lost, in this example, we don't
                                        deal with multiple master situation */
  default:
    I2CMasterState  = I2C_ARBITRATION_LOST;
    LPC_I2C->CONCLR = I2CONCLR_SIC;
    break;
  }
  return;
}
/*****************************************************/
void i2c_init(void) {
  LPC_SYSCON->PRESETCTRL |= (1 << 1);
  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 5);

  if ((LPC_SYSCON->SYSAHBCLKCTRL & (1 << 16)) != 1) {
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);    // Enable clock IOCON
    while ((LPC_SYSCON->SYSAHBCLKCTRL & (1 << 16)) == 1)
      ;
  }

  LPC_IOCON->PIO0_4 &= ~0x3F;
  LPC_IOCON->PIO0_4 |= 0x01;
  LPC_IOCON->PIO0_5 &= ~0x3F;
  LPC_IOCON->PIO0_5 |= 0x01;

  LPC_I2C->CONCLR |= (1 << 2) | (1 << 5) | (1 << 6);

  LPC_I2C->SCLL = 0X000000F0;    // 100KHz
  LPC_I2C->SCLH = 0X000000F0;

  //  LPC_I2C->SCLL = 0X0000003C; // 400KHz
  //  LPC_I2C->SCLH = 0X0000003C;

  NVIC_EnableIRQ(I2C_IRQn);

  LPC_I2C->CONSET |= I2CONSET_I2EN;
}
/*****************************************************/
uint32_t i2c_start(void) {
  uint32_t timeout = 0;
  uint32_t retVal  = 0x00;

  /*--- Issue a start condition ---*/
  LPC_I2C->CONSET = I2CONSET_STA; /* Set Start flag */

  /*--- Wait until START transmitted ---*/
  while (1) {
    if (I2CMasterState == I2C_STARTED) {
      retVal = 0x01;
      break;
    }
    if (timeout >= MAX_TIMEOUT) {
      retVal = 0x00;
      break;
    }
    timeout++;
  }
  return (retVal);
}
/*****************************************************/
uint32_t i2c_stop(void) {
  LPC_I2C->CONSET = I2CONSET_STO; /* Set Stop flag */
  LPC_I2C->CONCLR = I2CONCLR_SIC; /* Clear SI flag */

  /*--- Wait for STOP detected ---*/
  while (LPC_I2C->CONSET & I2CONSET_STO)
    ;
  return 0x01;
}

/*****************************************************/
uint32_t I2CEngine(void) {
  RdIndex = 0;
  WrIndex = 0;

  /*--- Issue a start condition ---*/
  LPC_I2C->CONSET = I2CONSET_STA; /* Set Start flag */

  I2CMasterState = I2C_BUSY;

  while (I2CMasterState == I2C_BUSY) {
    if (timeout >= MAX_TIMEOUT) {
      I2CMasterState = I2C_TIME_OUT;
      break;
    }
    timeout++;
  }
  LPC_I2C->CONCLR = I2CONCLR_STAC;

  return (I2CMasterState);
}

/*****************************************************/

/*****************************************************/

/*****************************************************/