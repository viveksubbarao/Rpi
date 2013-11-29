/* uart.h - UART initialization & communication */
 
#ifndef UART_H
#define UART_H
 
#include <stdint.h>
 
/*
 * Initialize UART0.
 */
void uart_init();

uint32_t uart_get_flags();
/*
 * Read a byte via UART0.
 */ 
uint8_t uart_getc();

/*
 * Transmit a byte via UART0.
 * uint8_t Byte: byte to send.
 */
void uart_putc(uint8_t byte);

/*
 * print a string to the UART one character at a time
 * const char *str: 0-terminated string
 */
void uart_puts(const char *str);

#endif // #ifndef UART_H
