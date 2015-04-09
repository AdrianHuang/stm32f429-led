/*
 * This program turns on/off LED(s) on stm32f429i discovery board.
 *
 * Reference: http://goo.gl/7iZIVC
 *
 * Adrian Huang <adrianhuang0701@gmail.com>
 *
 */

/*
 * Reset and Clock Control Register 
 */
#define RCC_ADDR 0x40023800
#define RCC_APB1ENR (*((volatile unsigned long *)(RCC_ADDR + 0x30)))

/*
 * GPIOG Register
 */
#define GPIOG_ADDR 0x40021800

/* GPIOG port mode register */
#define GPIOG_MODER 	(*((volatile unsigned long *) (GPIOG_ADDR)))

/* GPIOG port output type register */
#define GPIOG_OTYPER 	(*((volatile unsigned long *) (GPIOG_ADDR + 4)))

/* GPIOG port output speed mode register */
#define GPIOG_OSPEEDR 	(*((volatile unsigned long *) (GPIOG_ADDR + 8)))

/* GPIOG port bit set/reset register */
#define GPIOG_BSRR (*((volatile unsigned long *)(GPIOG_ADDR + 0x18)))

/* Green LED */
#define PG13 13

asm(".word 0x20001000");
asm(".word main");

int main()
{
	unsigned int c = 0;
	unsigned int shift = (PG13 * 2);

	RCC_APB1ENR = (1 << 6); /* GPIOGEN = 1 */

	GPIOG_MODER = (1 << shift); /* 1: General purpose output mode. */
	GPIOG_OSPEEDR = (1 << shift); /* 1: Medium speed. */
	GPIOG_OTYPER &= ~(1 << PG13); /* 0: Output push-pull. */

	while (1) {
		GPIOG_BSRR = (1 << 29); /* Reset bit: OFF */
		for (c = 0; c < 100000; c++);
			GPIOG_BSRR = (1 << PG13); /* Set bit: ON */
		for (c = 0; c < 100000; c++);
	}

	return 0;
}
