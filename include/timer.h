#ifndef TIMER_H
#define TIMER_H

#include <mmio.h>

#define ARM_TIMER_CTL 0x2000B408
#define ARM_TIMER_CNT 0x2000B420

static void timer_init ( void )
{
	//0xF9+1 = 250
	//250MHz/250 = 1MHz
	mmio_write(ARM_TIMER_CTL, 0x00F90000);
	mmio_write(ARM_TIMER_CTL, 0x00F90200);
}

static unsigned int timer_tick ( void )
{
	return(mmio_read(ARM_TIMER_CNT));
}

#endif // TIMER_H 

