#include "LPC11xx.h"

/*****************************************************/
// SPI SR FLAGS
#define SPP_SR_TFE_Pos (0U)
#define SPP_SR_TFE_Msk (0x1U << SPP_SR_TFE_Pos)
#define SPP_SR_TFE SPP_SR_TFE_Msk

#define SPP_SR_TNF_Pos (1U)
#define SPP_SR_TNF_Msk (0x1U << SPP_SR_TNF_Pos)
#define SPP_SR_TNF SPP_SR_TNF_Msk

#define SPP_SR_RNE_Pos (2U)
#define SPP_SR_RNE_Msk (0x1U << SPP_SR_RNE_Pos)
#define SPP_SR_RNE SPP_SR_RNE_Msk

#define SPP_SR_RFF_Pos (3U)
#define SPP_SR_RFF_Msk (0x1U << SPP_SR_RFF_Pos)
#define SPP_SR_RFF SPP_SR_RFF_Msk

#define SPP_SR_BSY_Pos (4U)
#define SPP_SR_BSY_Msk (0x1U << SPP_SR_BSY_Pos)
#define SPP_SR_BSY SPP_SR_BSY_Msk


#define SPI_CS_LOW LPC_GPIO2->DATA &= ~(1 << 2);
#define SPI_CS_HIGH LPC_GPIO2->DATA |= (1 << 2);

/*****************************************************/
void spi_init(void);
uint8_t Spi_transfer(uint8_t data);
/*****************************************************/