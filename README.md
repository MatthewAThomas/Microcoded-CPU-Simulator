# Microcoded RISC-V CPU Simulator

This project is an attempt to create a simulator of the microcoded, single-databus, 32-bit RISC-V CPU introduced in UC Berkeley's Introduction to Computer Architecture course (CS 152). This simulator abstracts at the functional unit level, and should be cycle accurate. More info about this CPU can be found here: https://inst.eecs.berkeley.edu/~cs152/sp24/assets/homeworks/hw01-handout.pdf


Current Approach (5/22/24):

Create submodule for each 'functional unit' (registers, ALU, etc) and 'connection' (signals, buses).

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


Instruction Cycle:
- instruction fetch
- instruction decode and execute
    Micro Operation Cycle:
    - ucode engine gets uOp, sets various control signals
    - write loop: loop through functional units. If enable signal is high, write data to the databus
        - functional units read from data bus or whatever registers feed into them 
        - e.g. the ALU would read from the A and B registers and calculate an operation; 
          it would write to the databus if ALUEn is set high
    - load loop: loop through the registers and any functional unit that loads from the databus. 
        - If load signal is high, latch data from databus
    - if instruction is completed, fetch next instruction (Instruction Cycle); else execute next uOp
