## Microcoded RISC-V CPU Emulator

This project is an attempt to create an emulator of the microcoded, single-databus, 32-bit RISC-V CPU introduced in UC Berkeley's Introduction to Computer Architecture course (CS 152). This emulator abstracts at the functional unit level, and should be cycle accurate. More info about this CPU can be found here: https://inst.eecs.berkeley.edu/~cs152/sp24/assets/homeworks/hw01-handout.pdf

Current Approach (5/27/24):

# The Emulator's Parts
There is a submodule for each 'functional unit' (registers, ALU, etc) and 'connection' (signals, buses).

- bus submodule
    - databus submodule: a signed 32 bit number
    - control signals submodule

- register template: defines register data type, declares all registers
- register file, register file tri-state buffer, A and B registers, MA register, IR submodule

- memory, memory tri-state buffer, busy flag submodule
    - includes a loader submodule for loading programs into memory
        - plan to only support loading raw machine code for now

- ALU, ALU tri-state buffer, zero flag submodule

- decode template: PC, RA, rd, rs1, rs2
- submodule for decoding instructions
    - populates the rd, rs1, rs2 fields
    - sets control signals
- ucode engine submodule (branch submodule?)

- immediate select, immediate select tri-state buffer submodule
    - the immediate select formats immediates: e.g. for U type instructions, it would output
      the immediate left shifted by 12

Lastly, main.c, which initializes all the submodules, the wires between them, and starts running the CPU.

# How the Emulator Works
Instruction Cycle:
- instruction fetch and decode
    - FETCH0
        - D microbranch invokes instruction decode
- instruction execute

- Micro Operation Cycle:
    - ucode engine gets uOp, sets various control signals
    - write loop: loop through functional units. If enable signal is high, write data to the databus
        - functional units read from data bus or whatever registers feed into them 
        - e.g. the ALU would read from the A and B registers and calculate an operation; 
            it would write to the databus if ALUEn is set high
    - load loop: loop through the registers and any functional unit that loads from the databus. 
        - If load signal is high, latch data from databus
    - if instruction is completed, fetch next instruction (Instruction Cycle); else execute next uOp

# Running the Emulator
Programs run on the emulator are written in machine code. The code is to be written to a text file located in the
programs subdirectory. To load a program into memory, set its path in the load function in loader.c

Formatting Programs:
Each line containing machine code represents four bytes of memory.
Each line of machine code is expected to be 12 characters long, including spaces but not including comments. Comments are 
denoted with the pound (#) sign. A comment may be written on a line by itself, or on a line after machine code.
Uppercase and lowercase characters are both excepted. Instructions and data types sized a word or larger
are expected to be word aligned (i.e. they should start at the beginning of a line). An example of code that 
does not violate formatting is shown below:

DE AD be ef
\# the line immediately below is empty (just new line character)

  
CafeD00d # the line immediately above has a couple of spaces but is otherwise blank
123 4 5678

The size of the "physical" memory is defined by the macro MEM_SIZE in mem.c. It is assumed that programs will be running
bare-metal, so the entire program must be loaded into physical memory: addresses 0 through MEM_SIZE - 1. Currently,
memory is 1024 bytes.  
