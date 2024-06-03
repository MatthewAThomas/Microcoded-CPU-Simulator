# Microcoded RISC-V CPU Emulator

Still under development.

This project is an attempt to create an emulator of the microcoded, single-databus, 32-bit RISC-V CPU introduced in UC Berkeley's Introduction to Computer Architecture course (CS 152). This emulator abstracts at the functional unit level, and should be cycle accurate. More info about this CPU can be found here: https://inst.eecs.berkeley.edu/~cs152/sp24/assets/homeworks/hw01-handout.pdf

Current Approach (5/27/24):

## How the Emulator Works
Instruction Cycle:
- instruction fetch and decode
    - FETCH0: D microbranch invokes instruction decode
- instruction execute
    - ucode engine gets uOp, sets various control signals
    - write loop: loop through functional units. If enable signal is high, write data to the databus
        - e.g. the ALU would read from the A and B registers and calculate an operation; 
            it would write to the databus if ALUEn is set high
    - load loop: loop through the registers and any functional unit that loads from the databus - if signaled to, latch data from databus
    - if instruction is completed, fetch next instruction (Instruction Cycle); else execute next uOp

## Running the Emulator
Programs ran on the emulator are written in machine code. The code is to be written to a text file located in the
**programs** subdirectory. To load a program into memory, set its path in the load function in loader.c

Formatting Programs:
The CPU uses little-endian byte ordering.
Each line containing machine code represents four bytes of memory.
Each line of machine code is expected to be 12 characters long, including spaces but not including comments. Comments are 
denoted with the pound (#) sign. A comment may be written on a line by itself, or on a line after machine code.
Uppercase and lowercase characters are both excepted. Instructions and data types sized a word or larger
are expected to be word aligned (i.e. they should start at the beginning of a line). An example of code that 
does not violate formatting is shown below:

    DE AD be ef
    # the line immediately below is empty (just new line character)

  
    CafeD00d # the line immediately above has a couple of spaces but is otherwise blank
    123 4 5678

The text section should be written first, followed by the data section.
The size of the "physical" memory is defined by the macro MEM_SIZE in mem.c. It is assumed that programs will be running
bare-metal, so the entire program must be loaded into physical memory: addresses 0 through MEM_SIZE - 1. Currently,
memory is 1024 bytes.  

## The Emulator's Parts
There is a submodule for each 'functional unit' (registers, ALU, etc) and 'connection' (signals, buses).
- bus submodule (bus.c, bus.h)
    - databus submodule: a signed 32 bit number
    - control signals submodule
- register template: defines register data type, declares all registers (register.h)
- register file, A and B registers, MA register, IR submodule (register.c)
- memory, busy flag submodule (mem.c)
    - includes a loader submodule for loading programs into memory (loader.c)
- ALU, zero flag submodule (alu.c)
- ucode engine submodule (ucode-engine.c)
- immediate select, immediate select tri-state buffer submodule (immsel.c)
    - the immediate select formats immediates: e.g. for U type instructions, it would output
      the immediate left shifted by 12
Lastly, main.c, which initializes all the submodules and starts running the CPU.

## Future Changes
Allow the emulator to take inputs for the size of memory and path to the program to be run. 