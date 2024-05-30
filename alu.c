#include "alu.h"
#include "call-functional-unit.h"
#include "bus.h"
#include "register.h"

uint8_t ZERO_FLAG = 0;

/* Each ALU Op takes two integers and returns an integer */
int32_t (* ALU_Ops[NUM_ALU_OPS]) (int32_t A_input, int32_t B_input);

/* ---------- define the operations -------------*/
int32_t COPY_A (int32_t A_input, int32_t B_input) {
    int32_t output = A_input;
    ZERO_FLAG = (output == 0);
    return output;
}
int32_t COPY_B (int32_t A_input, int32_t B_input) {
    int32_t output = B_input;
    ZERO_FLAG = (output == 0);
    return output;
}
int32_t INC_A_1 (int32_t A_input, int32_t B_input) {
    int32_t output = A_input + 1;
    ZERO_FLAG = (output == 0);
    return output;
}
int32_t DEC_A_1 (int32_t A_input, int32_t B_input) {
    int32_t output = A_input - 1;
    ZERO_FLAG = (output == 0);
    return output;
}
int32_t INC_A_4 (int32_t A_input, int32_t B_input) {
    int32_t output = A_input + 4;
    ZERO_FLAG = (output == 0);
    return output;
}
int32_t DEC_A_4 (int32_t A_input, int32_t B_input) {
    int32_t output = A_input - 4;
    ZERO_FLAG = (output == 0);
    return output;
}
int32_t ADD (int32_t A_input, int32_t B_input) {
    int32_t output = A_input + B_input;
    ZERO_FLAG = (output == 0);
    return output;
}
int32_t SUB (int32_t A_input, int32_t B_input) {
    int32_t output = A_input - B_input;
    ZERO_FLAG = (output == 0);
    return output;
}
int32_t SLT (int32_t A_input, int32_t B_input) {
    int32_t output = (A_input < B_input);
    ZERO_FLAG = (output == 0);
    return output;
}
int32_t SLTU (int32_t A_input, int32_t B_input) {
    int32_t output = ((unsigned) A_input) < ((unsigned) B_input);
    ZERO_FLAG = (output == 0);
    return output;
}
int32_t AND (int32_t A_input, int32_t B_input) {
    int32_t output = A_input & B_input;
    ZERO_FLAG = (output == 0);
    return output;
}
int32_t OR (int32_t A_input, int32_t B_input) {
    int32_t output = A_input | B_input;
    ZERO_FLAG = (output == 0);
    return output;
}
int32_t XOR (int32_t A_input, int32_t B_input) {
    int32_t output = A_input ^ B_input;
    ZERO_FLAG = (output == 0);
    return output;
}
int32_t SLL (int32_t A_input, int32_t B_input) {
    int32_t output = A_input << B_input;
    ZERO_FLAG = (output == 0);
    return output;
}
int32_t SRL (int32_t A_input, int32_t B_input) {
    int32_t output = ((unsigned) A_input) >> B_input;
    ZERO_FLAG = (output == 0);
    return output;
}
int32_t SRA (int32_t A_input, int32_t B_input) {
    int32_t output = A_input >> B_input;
    ZERO_FLAG = (output == 0);
    return output;
}


/* Functions that define interactions with the ALU */
void init_alu_unit(void) {
    ALU_Ops[0] = COPY_A;
    ALU_Ops[1] = COPY_B;
    ALU_Ops[2] = INC_A_1;
    ALU_Ops[3] = DEC_A_1;
    ALU_Ops[4] = INC_A_4;
    ALU_Ops[5] = DEC_A_4;
    ALU_Ops[6] = ADD;
    ALU_Ops[7] = SUB;
    ALU_Ops[8] = SLT;
    ALU_Ops[9] = SLTU;
    ALU_Ops[10] = AND;
    /* The following were not a part of the specified ALUOps for this CPU, but
       I added them to make implementing instructions a little easier */
    ALU_Ops[11] = OR;
    ALU_Ops[12] = XOR;
    ALU_Ops[13] = SLL;
    ALU_Ops[14] = SRL;
    ALU_Ops[15] = SRA;
}

void exec_alu_unit(void) {
    if (CONTROL_SIGNALS.ALUEn) {
        int32_t (* op) (int32_t, int32_t) = ALU_Ops[CONTROL_SIGNALS.ALUOp];
        DATA_BUS = op(A.value, B.value);
    }
}