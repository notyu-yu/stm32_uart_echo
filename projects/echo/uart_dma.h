#include "uart.h"

void uart_tx_start(void * data, size_t size);
void uart_tx_wait(void);
void uart_rx_start(void * buffer, size_t size);
void uart_rx_wait(void);
void uart_dma_init(void);
