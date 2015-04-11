/*
 * System initialization for stm32f429i discovery board.
 *
 * Reference:	http://goo.gl/7iZIVC
 *		https://github.com/jserv/mini-arm-os
 *
 * Adrian Huang <adrianhuang0701@gmail.com>
 *
 */
#include "regs.h"

#define SP 0x20010000

extern unsigned int _etext, _data, _edata, _bss, _ebss;

typedef void (*isr_handler) (void);

void reset_handler(void);
void systick_handler(void);

__attribute__ ((section(".isr_vector"))) isr_handler isr_vector_table[] =
{
	(isr_handler) SP, 	/* Exception No.0: Initial Stack Pointer  */
	reset_handler,		/* Exception No.1: Reset Handler 	  */
				/* Exceptions No.2~No14 are ignored here. */
	[15] = systick_handler,	/* Exception No.15: Initial Stack Pointer */
};

static void systick_enable()
{
	SYSTICK->reload = 0xffffff;
	SYSTICK->current = 0;
	SYSTICK->ctrl |= (SYSTICK_CTRL_EN | SYSTICK_CTRL_INT |
			SYSTICK_CTRL_CLKSRC_CPU);
}

void reset_handler(void)
{
	unsigned int *src, *dst;
	unsigned int c, i;

	src = &_etext;
	dst = &_data;

	while (dst < &_edata)
		*dst++ = *src++;

	dst = &_bss;
	while (dst < &_ebss)
		*dst++ = 0;

	systick_enable();

	led_init();

	led_blink();
}

void systick_handler(void)
{
	led_increment_index();
}
