
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

// The raspberry pi firmware at the time this was written defaults
// loading at address 0x8000.  Although this bootloader could easily
// load at 0x0000, it loads at 0x8000 so that the same binaries built
// for the SD card work with this bootloader.  Change the ARMBASE
// below to use a different location.

#include <uart.h>
#include <timer.h>
#include <mmio.h>

#define ARMBASE 0x9000

extern void BRANCHTO ( unsigned int );

unsigned char xstring[256];

void display_msg(void)
{
	uart_init();
	uart_putc('\r');
	uart_putc('\n');
	uart_putc('T');
	uart_putc('r');
	uart_putc('a');
	uart_putc('n');
	uart_putc('s');
	uart_putc('f');
	uart_putc('e');
	uart_putc('r');
	uart_putc(' ');
	uart_putc('y');
	uart_putc('o');
	uart_putc('u');
	uart_putc('r');
	uart_putc(' ');
	uart_putc('b');
	uart_putc('i');
	uart_putc('n');
	uart_putc('a');
	uart_putc('r');
	uart_putc('y');
	uart_putc('\n');
}

int notmain ( void )
{
	unsigned int ra;
	unsigned int rx;
	unsigned int block;
	unsigned int state;
	unsigned int addr;
	unsigned int crc;
	int i = 0;

	// Initialize mini UART
	uart_init();
	timer_init();

	display_msg();

	//SOH 0x01
	//ACK 0x06
	//NAK 0x15
	//EOT 0x04

	//block numbers start with 1

	//132 byte packet
	//starts with SOH
	//block number byte
	//255-block number
	//128 bytes of data
	//checksum byte (whole packet)
	//a single EOT instead of SOH when done, send an ACK on it too

	block = 1;
	state = 0;
	addr = ARMBASE;
	crc = 0;
	rx = timer_tick();

	while(1)
	{
		ra = timer_tick();

		if((ra -rx) >= 4000000) {
			uart_putc(0x15);
			rx += 4000000;
		}

		if (uart_get_flags() & (1 << 4))
			continue;

		xstring[state] = uart_getc();
		
		rx = timer_tick();

		if(state == 0) {
			if(xstring[state] == 0x04) {
				uart_putc(0x06);
				BRANCHTO(ARMBASE);
				break;
			}
		}

		switch(state) {
			case 0: {
					if(xstring[state] == 0x01) {
						crc = xstring[state];
						state++;
					} else {
						uart_putc(0x15);
					}
					break;
				}

			case 1: {
					if(xstring[state] == block) {
						crc += xstring[state];
						state++;
					} else {
						state = 0;
						uart_putc(0x15);
					}
					break;
				}

			case 2: {
					if(xstring[state] == (0xFF - xstring[state-1]))	{
						crc += xstring[state];
						state++;
					} else {
						uart_putc(0x15);
						state = 0;
					}
					break;
				}

			case 131: {
					  crc &= 0xFF;
					  if(xstring[state] == crc) {
						  for(ra = 0 ; ra < 128 ; ra++) {
							  PUT8(addr++, xstring[ra+3]);
						  }
						  uart_putc(0x06);
						  block = (block + 1) & 0xFF;
					  } else {
						  uart_putc(0x15);
					  }
					  state = 0;
					  break;
				  }

			default: {
					 crc += xstring[state];
					 state++;
					 break;
				 }
		}
	}
	return(0);
}


//-------------------------------------------------------------------------
//
// Copyright (c) 2012 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------
