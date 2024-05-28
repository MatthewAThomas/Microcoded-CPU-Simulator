#include "ucode-engine.h"
#include "register.h"
#include "mem.h"
#include "immsel.h"
#include "microcode.h"
#include "bus.h"
#include "call-functional-unit.h"
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

uint8_t OPCODE;

/* 0 -> PC, 1 -> RA, 2 -> rd, 3 -> rs1, 4 -> rs2 */
uint8_t REGISTER_FILE_MUX[5] = {32, 1, 0, 0, 0};



/*-------------------------------------------------- STATE DICTIONARY -------------------------------------------------*/

typedef struct {
    char *state;
    int state_index;
    uint8_t opcode;
} state_dictionary;

/* Each micro-operation corresponds to an index of the MICROCODE array.
   The state_dictionary keeps track of the indices of certain microperations.
   NUM_STATES == the number of micro-operations with labels (e.g. FETCH0, NOP0, etc).
*/
#define NUM_STATES 2
state_dictionary STATE_DICTIONARY[NUM_STATES];

/* If too few or too many states are read, returns false. Else true */
bool initialize_state_dictionary(void) {
    int dictionary_index = 0;
    for (int state_index = 0; dictionary_index < NUM_STATES; state_index++) {
        char *state = MICROCODE[state_index].state;

        if (strlen(state) > 0) {
            STATE_DICTIONARY[dictionary_index].state = state;
            STATE_DICTIONARY[dictionary_index].state_index = state_index;
            dictionary_index++;
        }

        /* Return if the end of the microcode is reached. NOP0 should be the end of the microcode. */
        if (!strcmp(state, "NOP0"))
            return (dictionary_index == NUM_STATES);
    }

    /* Unreachable */
    printf("read too many states\n");
    return false;
}

/* Returns the line number (zero-indexed) of the next state.
   If the state is not found, -1 is returned 
*/
int label_to_state_index(char *next_state) {
    if (!strcmp(next_state, ""))
        

    for (int i = 0; i < NUM_STATES; i++) {
        char *state = STATE_DICTIONARY[i].state;
        
        if (!strcmp(state, next_state))
            return STATE_DICTIONARY[i].state_index;
    }

    return -1;
}

/* Returns the line number (zero-indexed) of the uop corresoponding to an instruction.
   If the uop is not found, -1 is returned 
*/
int opcode_to_state_index(void) {
    for (int i = 0; i < NUM_STATES; i++) {
        uint8_t opcode = STATE_DICTIONARY[i].opcode;
        
        if (opcode == OPCODE)
            return STATE_DICTIONARY[i].state_index;
    }

    return -1;
}



/* --------------------------------------------------- uCODE ENGINE -------------------------------------------------*/

/* The MICROCODE index of the current micro-operation */
int STATE_INDEX;

void init_ucode_engine(void) {
    STATE_INDEX = 0;
}

void decode(int32_t instruction) {
    OPCODE = instruction & 0b1111111;

    uint8_t rd = (instruction >> 7) & 0b1111111;
    uint8_t rs1 = (instruction >> 15) & 0b1111111;
    uint8_t rs2 = (instruction >> 20) & 0b1111111;
    REGISTER_FILE_MUX[2] = rd;
    REGISTER_FILE_MUX[3] = rs1;
    REGISTER_FILE_MUX[4] = rs2;
}

void set_control_signals(uint8_t *control_signals) {
    CONTROL_BUS.IRLd = control_signals[0];
    CONTROL_BUS.RegSel = control_signals[1];
    CONTROL_BUS.RegWr = control_signals[2];
    CONTROL_BUS.RegEn = control_signals[3];
    CONTROL_BUS.ALd = control_signals[4];
    CONTROL_BUS.BLd = control_signals[5];
    CONTROL_BUS.ALUOp = control_signals[6];
    CONTROL_BUS.ALUEn = control_signals[7];
    CONTROL_BUS.MALd = control_signals[8];
    CONTROL_BUS.MemWr = control_signals[9];
    CONTROL_BUS.MemEn = control_signals[10];
    CONTROL_BUS.ImmSel = control_signals[11];
    CONTROL_BUS.ImmEn = control_signals[12];
}

void exec_functional_units(void) {
    // "write loop" (README -> How the Emulator Works)
    exec_memory_unit();
    exec_imm_sel_unit();
    exec_alu_unit();
    write_regs();
    // "load loop" (README -> How the Emulator Works)
    load_regs();
}

/* Returns index of next micro-op to be exectued. -1 If index not found. */
int get_next_uop(micro_op current_op) {
    // get next uop to execute
    char *uBr = current_op.uBr;

    if (!strcmp(uBr, "D")) {
        decode(IR.value);
        return opcode_to_state_index();
    }

    if (!strcmp(uBr, "N"))
        return STATE_INDEX + 1;

    if (!strcmp(uBr, "S")) {
        if (BUSY_FLAG == 0)
            return STATE_INDEX + 1;
        else
            return STATE_INDEX;
    }

    if (!strcmp(uBr, "J")) {
        char *next_state = current_op.next_state;
        return label_to_state_index(next_state);
    }

    // TODO: IMPLEMENT EZ, NZ

    printf("Invalid next state provided\n");
    return -1;
}

void exec_ucode_engine(void) {
    // TODO: figure out which instruction stops the program
    while (true) {
        micro_op current_op = MICROCODE[STATE_INDEX];
        uint8_t *control_signals = current_op.control_signals;

        set_control_signals(control_signals);
        exec_functional_units();
        STATE_INDEX = get_next_uop(current_op);
    }
}
