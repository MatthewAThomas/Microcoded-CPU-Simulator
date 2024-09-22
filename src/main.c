#include "call-functional-unit.h"
#include "ucode-engine.h"
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char **argv) {
    char *program = "test-add-ld-st.txt";

    if (argc == 2)
        program = argv[1];
    if (argc > 2) {
        printf("Too many arguments provided to emulator\n");
        return -1;
    }

    /* Initialize functional units */    
    if (init_memory_unit(program) == false) {
        printf("Error encountered while initializing the memory unit\n");
        return -1;
    }
    init_imm_sel_unit();
    init_alu_unit();
    init_regs();
    if (init_ucode_engine() == false) {
        printf("Error encountered while initializising the ucode engine\n");
        return -1;
    }

    /* Run the processor */
    int exit_code = exec_ucode_engine();
    return exit_code;
}