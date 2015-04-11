/*
 * This program turns on/off LED(s) on stm32f429i discovery board.
 *
 * Reference: 	http://goo.gl/7iZIVC
 *		https://github.com/jserv/mini-arm-os
 *
 * Adrian Huang <adrianhuang0701@gmail.com>
 *
 */
#include "regs.h"

/*
 * GPIOG Register
 */
#define GPIOG_ADDR 0x40021800
#define GPIOG	((volatile struct gpio_regs *) GPIOG_ADDR)

/*
 * LED
 */
#define PG13 13 /* The pin number of Green led. */
#define PG14 14 /* The pin number of Red led. */

/* LED list */
unsigned int leds[] = {
	PG13,
	PG14
};

static int num_leds = (sizeof(leds)/sizeof(leds[0]));
static int led_index;

static void led_cfg(unsigned int pin)
{
	unsigned int shift = (pin * 2);

	GPIOG->moder |= (1 << shift); 	/* 1: General purpose output mode */
	GPIOG->ospeedr |= (1 << shift); /* 1: Medium speed */
	GPIOG->otyper &= ~(1 << pin); 	/* 0: Output push-pull */
}

void led_blink()
{
	unsigned int i, c;

	while (1) {
		i = led_index;

		/* Reset bit: ON */
		GPIOG->bsrr = (1 << leds[i]);
		for (c = 0; c < 100000; c++);

		/* Reset bit: OFF */
		GPIOG->bsrr = (1 << (leds[i] + 16));
		for (c = 0; c < 100000; c++);
	}
}

void led_increment_index()
{
	if (++led_index >= num_leds)
		led_index = 0;
}

void led_init()
{
	int i;

	/* Enable the clock of GPIO G */
	RCC_AHB1ENR = (1 << 6);

	for(i=0;i<num_leds;i++)
		led_cfg(leds[i]);
}
