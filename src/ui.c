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

void print_menu(void) {
    printf("n -> execute next micro-operation\n");
    printf("o -> print current micro-operation\n");
    printf("b -> print state of control and data buses\n");
    printf("r -> print state of registers\n");
    printf("m -> print state of memory\n");
    printf("q -> exit simulator\n");
}

int print_state(micro_op *op) {
    if (strcmp("FETCH0", op -> state))// && strcmp("", op -> state))
        instruction = op -> state;

    if (instruction != NULL)
        printf("%s\n\n", instruction);
    
    char buffer[2];
    scanf("%c", buffer);
    buffer[1] = '\00';
    //clear();
    while (buffer[0] != 'n') {
        if (buffer[0] == 'o')
            print_micro_op(op);
        if (buffer[0] == 'b')
            print_bus();
        if (buffer[0] == 'r')
            print_registers();
        if (buffer[0] == 'm')
            print_memory();
        if (buffer[0] == 'h')
            print_menu();

        if (buffer[0] == 'q')
            return 1;

        scanf("%c", buffer);
        clear();
    }

    return 0;
}