
PREFIX ?= /home/viveks/workspace/Rpi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian
ARMGNU ?= $(PREFIX)/bin/arm-linux-gnueabihf

# source files
SOURCES_ASM := $(wildcard *.S)
SOURCES_C   := $(wildcard *.c)
SOURCES_C   += ../common/uart.c
  
# object files
OBJS        := $(patsubst %.S,%.o,$(SOURCES_ASM))
OBJS        += $(patsubst %.c,%.o,$(SOURCES_C))

INCLUDE = -I../include
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding 

all : kernel.img 

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc
	rm -f *.clang.s


#vectors.o : vectors.s
#	$(ARMGNU)-as vectors.s -o vectors.o

#bootloader05.o : bootloader05.c
#	$(ARMGNU)-gcc $(INCLUDE) $(COPS) -c bootloader05.c -o bootloader05.o

#periph.o : periph.c
#	$(ARMGNU)-gcc $(COPS) -c periph.c -o periph.o

uart.o : ../common/uart.c
	$(ARMGNU)-gcc $(INCLUDE) $(COPS) -c ../common/uart.c -o uart.o

#kernel.img : $(OBJS) loader 
#	$(ARMGNU)-ld vectors.o uart.o bootloader05.o -T loader -o bootloader05.elf
#	$(ARMGNU)-objdump -D bootloader05.elf > bootloader05.list
#	$(ARMGNU)-objcopy bootloader05.elf -O ihex bootloader05.hex
#	$(ARMGNU)-objcopy bootloader05.elf -O binary kernel.img

kernel.elf: $(OBJS) loader
	$(ARMGNU)-ld $(OBJS) -Tloader -o $@

kernel.img: kernel.elf
	$(ARMGNU)-objcopy kernel.elf -O binary kernel.img

# C.
%.o: %.c Makefile
	$(ARMGNU)-gcc $(INCLUDE) $(CFLAGS) -c $< -o $@

# AS.
%.o: %.S Makefile
	$(ARMGNU)-gcc -mcpu=arm1176jzf-s $(ASFLAGS) -c $< -o $@

