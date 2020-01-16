#include "LPC11xx.h"

/*****************************************************/
// USART SR FLAGS
#define LSR_THRE_Pos (5U)
#define LSR_THRE_Msk (0x1U << LSR_THRE_Pos)
#define LSR_THRE LSR_THRE_Msk

#define LSR_TEMT_Pos (6U)
#define LSR_TEMTF_Msk (0x1U << LSR_TEMT_Pos)
#define LSR_TEMT SPP_SR_TNF_Msk

#define LSR_RDR_Pos (0U)
#define LSR_RDR_Msk (0x1U << LSR_RDR_Pos)
#define LSR_RDR LSR_RDR_Msk

/*****************************************************/
void uart_init(uint32_t br);
void uart_send(char c);
void uart_send_string(char *str);
void uart_send_buffer(uint8_t *buff, uint16_t len);
/*****************************************************/