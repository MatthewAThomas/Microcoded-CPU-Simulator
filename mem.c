#include "mem.h"
#include "loader.h"
#include "register.h"
#include "call-functional-unit.h"
#include "bus.h"

#define MEM_SIZE 1024
uint8_t BUSY_FLAG = 0;

/* MEM_SIZE defined in loader.h */
uint8_t MEMORY[MEM_SIZE];

/* Initializes memory: loads the program */
void init_memory_unit(void) {
    // TODO: write a function that can load machine code into MEM (in loader.c)
    ;;
}

// uint8_t MemWr;
// uint8_t MemEn;


static void write(int32_t data, int32_t address) {
    uint8_t first = 0b11111111 & data;
    uint8_t second = 0b11111111 & (data >> 8);
    uint8_t third = 0b11111111 & (data >> 16);
    uint8_t fourth = 0b11111111 & (data >> 24);

    MEMORY[address] = first;
    MEMORY[address + 1] = second;
    MEMORY[address + 2] = third;
    MEMORY[address + 3] = fourth;
}
static int32_t read(int32_t address) {
    int32_t first = MEMORY[address];
    int32_t second = (MEMORY[address + 1]) << 8;
    int32_t third = (MEMORY[address + 2]) << 16;
    int32_t fourth = (MEMORY[address + 3]) << 24;

    int32_t data = first | second | third | fourth;
    return data;
}

// assuming the memory unit has 1 cycle latency
// i.e. busy flag is always 0
void exec_memory_unit(void) {
    int32_t address = MA.value;

    if (CONTROL_BUS.MemWr)
        write(DATA_BUS, address);

    if (CONTROL_BUS.MemEn)
        DATA_BUS = read(address);
}