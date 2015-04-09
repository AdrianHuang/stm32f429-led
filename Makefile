CROSS_COMPILE ?= arm-none-eabi-

TARGET := blink.bin

FLASH_CMD := openocd \
	-f board/stm32f429discovery.cfg \
	-c "init" \
	-c "reset init" \
	-c "flash probe 0" \
	-c "flash info 0" \
	-c "stm32f2x mass_erase 0" \
	-c "flash write_bank 0 $(TARGET) 0x0" \
	-c "reset run" -c shutdown

.PHONY: all
all: $(TARGET)

blink.o: blink.c
	$(CROSS_COMPILE)gcc -mcpu=cortex-m4 -mthumb -nostartfiles -c blink.c -o blink.o

blink.out: blink.o simple.ld
	$(CROSS_COMPILE)ld -T simple.ld -o blink.out blink.o

blink.bin: blink.out
	$(CROSS_COMPILE)objcopy -j .text -O binary blink.out blink.bin

.PHONY += install
install: $(TARGET)
	$(shell ${FLASH_CMD})

clean:
	rm -f *.o *.out *.bin

