#include "uart.h"

#define READSIZE(buffer) *(size_t *)buffer
#define PADDINGSIZE 4

// Returns pointer to msg without padding
static char * msg_offset(char * msg) {
	return msg + PADDINGSIZE;
}

int main(void) {
	char debug_msg[BUFFER_SIZE] = {0};
	char * stripped_msg;
	size_t received_size=0;

	uart_init();
	led_init();

	while(1) {
		// Read received buffer size
		led_on(GREEN);
		uart_receive(msg_buffer, sizeof(size_t));
		received_size = READSIZE(msg_buffer) + PADDINGSIZE;
		memset(msg_buffer, 0, sizeof(size_t));
		led_off(GREEN);

		// Send back buffer content
		if (received_size > BUFFER_SIZE) {
			led_on(ORANGE);
			// Message too large
			sprintf(debug_msg, "Attempting to read %u bytes larger than buffer size %d.\n", (unsigned int)received_size, BUFFER_SIZE);
			uart_send(debug_msg, strlen(debug_msg));
			led_off(ORANGE);
		} else {
			/*
			sprintf(debug_msg, "Reading data.\n");
			uart_send(debug_msg, strlen(debug_msg));
			*/

			led_on(RED);
			// Zero out buffer and read message
			memset(msg_buffer, 0, sizeof(size_t));
			uart_receive(msg_buffer, received_size);
			led_off(RED);

			sprintf(debug_msg, "Received %u bytes with %d bytes of padding.\n", (unsigned int)received_size, PADDINGSIZE);
			uart_send(debug_msg, strlen(debug_msg));


			// Echo message
			led_on(BLUE);
			sprintf(debug_msg, "Sending %u bytes.\n", (unsigned int)strlen(stripped_msg));
			stripped_msg = msg_offset(msg_buffer);
			uart_send(stripped_msg, strlen(stripped_msg));
			memset(msg_buffer, 0, strlen(stripped_msg));
			led_off(BLUE);
		}
	}
}

