# 8-Bit CPU

### 1. Basic EEPROM Writer

The code in [`/eeprom-writer`](/eeprom-writer) is the basic writer that has function to handle reading and writing from an EEPROM chip. This version utilized the Atmel AT28C64B, a 64Kb memory device but could be used without any changes with smaller capacity Atmel EEPROMs of the same family and pinout design.

[Atmel AT28C64B Datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/doc0270.pdf)
64K (8K x 8) Parallel EEPROM with Page Write and Software Data Protection

![screenshot](https://github.com/mic-max/eeprom-writer/blob/master/pinout.png)

### 2. 8-Bit Decimal Display

The code in [`/multiplexed-display`](/multiplexed-display) is for programming an EEPROM to be used to decode 8-bit values and drive a 4-digit 7-segment display. It is currently able to represent integer values in: hexadecimal and both signed and unsigned decimal, the ability to switch encoding types is made possible by changing the two highest order bits on the EEPROMs memory address.

### 3. 8-Bit Computer Microcode

The code in [`/microcode-eeprom-programmer`](/microcode-eeprom-programmer) is for programming a pair of EEPROMs to serve as an instruction decoder for an 8-bit breadboard computer.

### 4. [TODO] Write Program to RAM

This will have code to allow writing assembly code directly to the breadboard computer when the arduino is hooked up to the four memory address lines and eight memory data inputs. Currently the CPU must be programmed by manually setting the dip switches.

### 5. [TODO] Custom Assembly Language

To be used in combination with the ability to write a program directly to the computer's memory. Create an arduino project that reads a file of commands such as: LDA 14, ADD 15, OUT. So it will remove the necessity of looking up command code binary values, and be less error prone.

I believe that is the extent this project will reach before increasing the computer's abilities with more RAM and computation power/complexity. Creating even a simple programming language and its compiler for a computer with 16 bytes of memory is nonsensical.