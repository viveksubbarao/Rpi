# Makefile - build script */
  
# build environment
PREFIX ?= /home/viveks/workspace/Rpi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian
ARMGNU ?= $(PREFIX)/bin/arm-linux-gnueabihf

# source files
SOURCES_ASM := $(wildcard *.S)
SOURCES_C   := $(wildcard *.c)
SOURCES_C   += ../common/uart.c
#  
# object files
OBJS        := $(patsubst %.S,%.o,$(SOURCES_ASM))
OBJS        += $(patsubst %.c,%.o,$(SOURCES_C))

# Build flags
DEPENDFLAGS := -MD -MP
INCLUDES    := -I ../include
BASEFLAGS   := -O2 -fpic -pedantic -pedantic-errors -nostdlib
BASEFLAGS   += -nostartfiles -ffreestanding -nodefaultlibs
BASEFLAGS   += -fno-builtin -fomit-frame-pointer -mcpu=arm1176jzf-s
WARNFLAGS   := -Wall -Wextra -Wshadow -Wcast-align -Wwrite-strings
WARNFLAGS   += -Wredundant-decls -Winline
WARNFLAGS   += -Wno-attributes -Wno-deprecated-declarations
WARNFLAGS   += -Wno-div-by-zero -Wno-endif-labels -Wfloat-equal
WARNFLAGS   += -Wformat=2 -Wno-format-extra-args -Winit-self
WARNFLAGS   += -Winvalid-pch -Wmissing-format-attribute
WARNFLAGS   += -Wmissing-include-dirs -Wno-multichar
WARNFLAGS   += -Wredundant-decls -Wshadow
WARNFLAGS   += -Wno-sign-compare -Wswitch -Wsystem-headers -Wundef
WARNFLAGS   += -Wno-pragmas -Wno-unused-but-set-parameter
WARNFLAGS   += -Wno-unused-but-set-variable -Wno-unused-result
WARNFLAGS   += -Wwrite-strings -Wdisabled-optimization -Wpointer-arith
WARNFLAGS   += -Werror
ASFLAGS     := $(INCLUDES) $(DEPENDFLAGS) -D__ASSEMBLY__
CFLAGS      := $(INCLUDES) $(DEPENDFLAGS) $(BASEFLAGS) $(WARNFLAGS)
CFLAGS      += -std=gnu99
  
# build rules
all: kernel.load

include $(wildcard *.d)

kernel.elf: $(OBJS) link-arm-eabi.ld
	$(ARMGNU)-ld $(OBJS) -Tlink-arm-eabi.ld -o $@

kernel.load: kernel.elf
	$(ARMGNU)-objcopy kernel.elf -O binary kernel.load

clean:
	$(RM) -f $(OBJS) *.d kernel.elf kernel.load

dist-clean: clean
	$(RM) -f *.d

# C.
%.o: %.c Makefile
	$(ARMGNU)-gcc $(CFLAGS) -c $< -o $@
 	 
# AS.
%.o: %.S Makefile
	$(ARMGNU)-gcc -mcpu=arm1176jzf-s $(ASFLAGS) -c $< -o $@
