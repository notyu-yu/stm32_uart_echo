Project files in projects/echo/

Usage:
run.sh: Compiles and burns the program onto the mcu. The reset button should be pressed after burning to start the program.
pc_echo: Sends input from stdin to mcu through UART. It needs root privilge to access the USB serial port.
config.h: Used to set max buffer size, serial device file, baudrate, and verbose option.

LED Indicators:
Green: Listening for message size.
Orange: Message size received but it exceeds the buffer size.
Red: Listening for message content.
Blue: Sending message back.

Connection:
PA2 is the TX pin, PA3 is the RX pin

Code organization:
uart.c: Provides interface to send and receive messages through UART, also include LED functions for indicator.
mcu_echo.c: Constantly listens to UART for message sent, and echos content back through UART. It expects the message size to be sent first, then message content.
pc_echo.c: Send message from stdin through UART.
