#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#define SERIALDEV "/dev/ttyUSB0"
#define BUFFERSIZE 1024
#define PADDINGSIZE 3

// Set up serial device
static void serial_setup(int fd) {
	struct termios serial_settings;
	tcgetattr(fd, &serial_settings);

	// Set buad rate
	cfsetispeed(&serial_settings, B115200);
	cfsetospeed(&serial_settings, B115200);

	serial_settings.c_cflag &= ~CRTSCTS; // Hardware based flow control off
	serial_settings.c_cflag |= CREAD | CLOCAL; // Turn on receiver
	serial_settings.c_iflag &= ~(IXON | IXOFF | IXANY); // Software based flow control off
	serial_settings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Set operation mode, canonical, enable input echo and receiving signals
	tcsetattr(fd, TCSANOW, &serial_settings);
}


int main(int argc, char ** argv) {
	int fd;
	char send_buffer[BUFFERSIZE] = {0};
	char receive_buffer[BUFFERSIZE*2] = {0};
	size_t msg_size = 0;

	// Open serial device
	fd = open(SERIALDEV, O_RDWR | O_NOCTTY);
	assert(fd>=0);
	serial_setup(fd);

	// Read message from stdin
	fgets(send_buffer, BUFFERSIZE, stdin);
	msg_size = strlen(send_buffer);
	
	// Send message to UART usb device and print return message
	// Use read/write functions
	printf("Sending message: %s\n", send_buffer);
	printf("Message size: %zu bytes\n", msg_size);
	assert(write(fd, &msg_size, sizeof(size_t)) == sizeof(size_t));
	assert(write(fd, send_buffer, msg_size) == msg_size);
	read(fd, receive_buffer, BUFFERSIZE);
	puts(receive_buffer);
	
	return 0;
}
