CROSS_COMPILE ?= arm-none-eabi-

TARGET := led.bin

FLASH_CMD := openocd \
	-f board/stm32f429discovery.cfg \
	-c "init" \
	-c "reset init" \
	-c "flash probe 0" \
	-c "flash info 0" \
	-c "stm32f2x mass_erase 0" \
	-c "flash write_bank 0 $(TARGET) 0x0" \
	-c "reset run" -c shutdown

CFLAGS = -mcpu=cortex-m4 -mthumb \
	 -nostartfiles -Tled.ld

.PHONY: all
all: $(TARGET)

$(TARGET): led.c sys_init.c
	$(CROSS_COMPILE)gcc $(CFLAGS) $^ -o led.elf
	$(CROSS_COMPILE)objcopy -Obinary led.elf led.bin

.PHONY += install
install: $(TARGET)
	$(shell ${FLASH_CMD})

clean:
	rm -f *.o *.elf *.bin
