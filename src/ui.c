#include <stdio.h>
#include <string.h>
#include "ui.h"

static char *instruction;

void print_state(char *micro_op_label) {
    if (strcmp("FETCH0", micro_op_label) && strcmp("", micro_op_label))
        instruction = micro_op_label;

    printf("%s\n\n", instruction);
    
    // print_micro_op();
    // print_bus();
    // print_registers();
    // print_memory();
}