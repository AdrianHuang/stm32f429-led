#ifndef __REG_H_
#define __REG_H_

struct gpio_regs {
	unsigned int moder;
	unsigned int otyper;
	unsigned int ospeedr;
	unsigned int pupdr;
	unsigned int idr;
	unsigned int odr;
	unsigned int bsrr;
	unsigned int lckr;
	unsigned int afr[2];
};

struct systick {
	unsigned int ctrl;
	unsigned int reload;
	unsigned int current;
	unsigned int calibration;
};

/* SysTick Base Address */
#define SYSTICK_BASE	0xE000E010
#define SYSTICK         ((volatile struct systick *) SYSTICK_BASE)

/* Fields of SysTick Control and Status Register */
#define SYSTICK_CTRL_EN		(1 << 0) /* System Tick Enable */
#define SYSTICK_CTRL_INT	(1 << 1) /* System Tick Interrupt */
#define SYSTICK_CTRL_CLKSRC_CPU	(1 << 2) /* System Tick Clock Source */

/*
 * Reset and Clock Control Register
 */
#define RCC_ADDR 0x40023800
#define RCC_AHB1ENR (*((volatile unsigned long *)(RCC_ADDR + 0x30)))

#endif
