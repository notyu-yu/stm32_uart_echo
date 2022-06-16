#include "../../include/stm32f411xe.h"
#include "../../include/system_stm32f4xx.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

extern char msg_buffer[BUFFER_SIZE];

void uart_init(void);
void uart_send(void * data, size_t size);
void uart_receive(void * buffer, size_t size);

typedef enum {
	GREEN=12,
	ORANGE,
	RED,
	BLUE
} led;

void led_init(void);
void led_on(led l);
void led_off(led l);
void led_toggle(led l);
