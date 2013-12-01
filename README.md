Rpi
===
The code in this repository is written for Raspberry Pi Model B
with 512 MB RAM although it should run with very little modifications
on older versions too.

This repo includes a bootloader and a very minimal kernel that just
prints some text onto the serial console.

The bootloader is actually code that is loaded by the Rpi firmaware
and which initializes UART and helps the user transfer his program
to Rpi memory and test it without having to remove the SD card from
the Rpi, plugging it into a desktop or laptop, transfering the program
and then inserting it into Rpi and booting it.

The bootloader communicates through serail console to a dumb terminal
like putty or minicom and uses xmodem to receive the user program.

Usage
=====

1. Transfer the bootloader binary (named kernel.img in the bootloader
   folder) to a SD card.
2. Insert the SD card into Rpi.
3. Use a terminal with xmodem capability (hyperterminal on Windows
   , minicom and sz on Linux).
4. Set the terminal parameters to 115200 Baud rate, 8-bits,1 stop bit
   no parity bits and no flow control.
4. Power up Rpi.
5. A message appears on the screen asking the user to transfer his
   binary.
6. Tranfer the binary and see it perform.

The bootloader is by default loaded at 0x8000, this inturn loads
the user binary at 0x9000 and jumps to that address after the transfer
is complete.

NOTE: Make sure to build you binary with a load address of 0x9000,
otherwise it might not work. I havent tested this properly though.

Acknowledgements
===============
David Welch dwelch@dwelch.com -- https://github.com/dwelch67/raspberrypi
	All people who have contributed to this -- http://wiki.osdev.org/ARM_RaspberryPi_Tutorial_C
