Project files in projects/echo/

Usage:
run.sh: Compiles and burns the program onto the mcu. The reset button should be pressed after burning to start the program.
pc_echo: Sends input from stdin to mcu through UART. It needs root privilge to access the USB serial port.
config.h: Used for compile time configuration. See configuration section.

LED Indicators:
Green: Listening for message size.
Orange: Message size received but it exceeds the buffer size.
Red: Listening for message content.
Blue: Sending message back.

Connection:
PA2 is the TX pin, PA3 is the RX pin

Code organization:
uart.c: Provides interface to send and receive messages through UART, also include LED functions for indicator.
uart_dma.c: Provides interface to send and receive UART message through DMA.
mcu_echo.c: Constantly listens to UART for message sent, and echos content back through UART. It expects the message size to be sent first, then message content.
pc_echo.c: Send message from stdin through UART.

Configuration:
BUFFERSIZE: Maximum message buffer size, note the noncanonical read buffer only accepts up to 4095 chars.
BAUDRATE: Set the baud rate for the transmission, use the B$(baud rate) macro. The mantissa and fraction bits for USARTDIV needs to be calculated and set manually in uart.c.
VERBOSE: Print some debug information when echoing.
SERIALDEV: Device file name of the USB to serial adapter.
USE_DMA: Whether or not to use DMA in mcu_echo.c.
PADDINSIZE: Number of 0 paddings in received string, usually 3 or 4.
