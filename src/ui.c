#include "ui.h"
#include "mem.h"
#include "register.h"
#include "bus.h"
#include <stdio.h>
#include <string.h>

#define clear() printf("\033[H\033[J")

static char *instruction;

void print_micro_op(micro_op *op) {
    printf("Current micro-operation:\n");
    printf("current state: %s\n next state: %s\n uBr: %s\n opcode: 0x%x\n funct3: 0x%x\n funct7: 0x%x\n",
           op -> state, op -> next_state, op -> uBr, op -> opcode, op -> funct3, op -> funct7);
}

void print_state(micro_op *op) {
    if (strcmp("FETCH0", op -> state) && strcmp("", op -> state))
        instruction = op -> state;

    printf("%s\n\n", instruction);
    
    // TODO: add logic so that user determines which of these functions run
    //       example - b => prints bus, r => prints registers, m => prints memory
    //                 n => return from print_state and execute the next micro-operation
    print_micro_op(op);
    print_bus();
    print_registers();
    print_memory();
}