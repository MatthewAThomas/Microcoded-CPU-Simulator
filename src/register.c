#include "register.h"
#include "ucode-engine.h"
#include "call-functional-unit.h"
#include "bus.h"
#include <stdio.h>

#define REGISTER_FILE_SIZE 33

struct Register IR = {0};
struct Register A = {0};
struct Register B = {0};
struct Register MA = {0};

/* REGISTER_FILE is indexed by RegSel (in CONTROL_SIGNALS)
   32 GPRs + PC
   PC is register 32
   RA is register 1
   rd, rs1, and rs2 are any of the other registers (0, 2, 3, ..., 31)
*/
struct Register REGISTER_FILE[REGISTER_FILE_SIZE] = {0};

/* Establish input and output wires of each register */
void init_regs(void) {
    for (int i = 0; i < REGISTER_FILE_SIZE; i++) {
        REGISTER_FILE[i].Ld_Wr = &(CONTROL_SIGNALS.RegWr);
    }

    IR.Ld_Wr = &(CONTROL_SIGNALS.IRLd);

    A.Ld_Wr = &(CONTROL_SIGNALS.ALd);

    B.Ld_Wr = &(CONTROL_SIGNALS.BLd);

    MA.Ld_Wr = &(CONTROL_SIGNALS.MALd);
}

/* The only registers that write directly to the data bus are in the register file. 
   All other registers feed into functional units; these units read the contents of 
   their respective registers each clock cycle. */
void write_regs(void) {
    struct Register r = REGISTER_FILE[REGISTER_FILE_MUX[CONTROL_SIGNALS.RegSel]];

    if (CONTROL_SIGNALS.RegEn)
        DATA_BUS = r.value;
}

void load_regs(void) {
    struct Register *r_pointer = &(REGISTER_FILE[REGISTER_FILE_MUX[CONTROL_SIGNALS.RegSel]]);
    if (*(r_pointer -> Ld_Wr)  
    && (REGISTER_FILE_MUX[CONTROL_SIGNALS.RegSel] != 0)) // x0 register should remain 0
        r_pointer -> value = DATA_BUS;

    if (*(IR.Ld_Wr))
        IR.value = DATA_BUS;

    if (*(A.Ld_Wr))
        A.value = DATA_BUS;

    if (*(B.Ld_Wr))
        B.value = DATA_BUS;

    if (*(MA.Ld_Wr))
        MA.value = DATA_BUS;
}

void print_registers(void) {
    for (int i = 0; i < REGISTER_FILE_SIZE; i++) {
        printf("Register x%d: val = %d, load/write = %u\n",
               i, REGISTER_FILE[i].value, REGISTER_FILE[i].Ld_Wr);
    }

    printf("         IR: val = %d, load/write = %u\n", IR.value, IR.Ld_Wr);
    printf("          A: val = %d, load/write = %u\n", A.value, A.Ld_Wr);
    printf("          B: val = %d, load/write = %u\n", B.value, B.Ld_Wr);
    printf("         MA: val = %d, load/write = %u\n", MA.value, MA.Ld_Wr);
}