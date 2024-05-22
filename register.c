#include "register.h"
#include "call-functional-unit.h"
#include "decode.h"
#include "bus.h"

#define REGISTER_FILE_SIZE 33

struct Register IR = {0};
struct Register A = {0};
struct Register B = {0};
struct Register MA = {0};

/* REGISTER_FILE is indexed by RegSel (in CONTROL_BUS)
   32 GPRs + PC
   PC is register 32
   RA is register 1
   rd, rs1, and rs2 are any of the other registers (0, 2, 3, ..., 31)
*/
struct Register REGISTER_FILE[REGISTER_FILE_SIZE] = {0};

/* Establish input and output wires of each register */
void init_regs(void) {
    for (int i = 0; i < REGISTER_FILE_SIZE; i++) {
        REGISTER_FILE[i].Ld_Wr = &(CONTROL_BUS.RegWr);
    }

    IR.Ld_Wr = &(CONTROL_BUS.IRLd);

    A.Ld_Wr = &(CONTROL_BUS.ALd);

    B.Ld_Wr = &(CONTROL_BUS.BLd);

    MA.Ld_Wr = &(CONTROL_BUS.MALd);
}

/* The only registers that write directly to the data bus are in the register file. 
   All other registers feed into functional units; these units read the contents of 
   their respective registers each clock cycle. */
void write_regs(void) {
    struct Register r = REGISTER_FILE[REGISTER_FILE_MUX[CONTROL_BUS.RegSel]];

    if (CONTROL_BUS.RegEn)
        DATA_BUS = r.value;
}

void load_regs(void) {
    struct Register r = REGISTER_FILE[REGISTER_FILE_MUX[CONTROL_BUS.RegSel]];
    if (*(r.Ld_Wr))
        r.value = DATA_BUS;

    if (*(IR.Ld_Wr))
        IR.value = DATA_BUS;

    if (*(A.Ld_Wr))
        A.value = DATA_BUS;

    if (*(B.Ld_Wr))
        B.value = DATA_BUS;

    if (*(MA.Ld_Wr))
        MA.value = DATA_BUS;
}