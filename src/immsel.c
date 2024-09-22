/*
The immediate select formats immediates: e.g. for U type instructions, it would output
the immediate left shifted by 12
*/


#include "call-functional-unit.h"
#include "register.h"
#include "bus.h"
#include <stdint.h>

#define INSTRUCTION_LENGTH 32

/*---------------- define immediate formats ------------------*/

int32_t I_TYPE (int32_t instruction) {
    int i_type_imm_length = 12;
    int32_t immediate = instruction >> 20;

    int funct3 = instruction >> 12;
    funct3 &= 0b111;

    // if instruction is sltiu, don't sign extend it
    int sltiu_funct3 = 0b011;
    if (funct3 == sltiu_funct3)
        immediate &= 0b111111111111;

    return immediate;
}
int32_t I_STAR_TYPE (int32_t instruction) {
    int i_star_type_imm_length = 5;
    int32_t immediate = instruction >> 20;
    immediate &= 0b11111; // i star type instruction immediates are not sign extended
    return immediate;
}
int32_t S_TYPE (int32_t instruction) {
    int s_type_lower_imm_length = 5;
    int s_type_upper_imm_length = 7;
    int s_type_imm_length = 12;

    int32_t lower = instruction >> 7;
    lower &= 0b11111;

    int32_t upper = (instruction >> 25) << s_type_lower_imm_length; 
    int32_t immediate = upper | lower;
    
    return immediate;
}
int32_t B_TYPE (int32_t instruction) {
    int32_t bits_1_through_4 = instruction >> 8;
    bits_1_through_4 &= 0b1111;
    bits_1_through_4 <<= 1;

    int32_t bits_5_through_10 = instruction >> 25;
    bits_5_through_10 &= 0b111111;
    bits_5_through_10 <<= 5;

    int32_t bit_11 = instruction >> 7;
    bit_11 &= 0b1;
    bit_11 <<= 11;

    int32_t bit_12 = instruction >> 31;
    bit_12 <<= 12;

    int immediate_length = 13;
    int32_t immediate = bit_12 | bit_11 | bits_5_through_10 | bits_1_through_4;
    return immediate;
}
int32_t U_TYPE (int32_t instruction) {
    int immediate_length = 20;
    int32_t immediate = (instruction >> 12) << 12;
    return immediate;
}
int32_t J_TYPE (int32_t instruction) {
    int32_t bits_1_through_10 = instruction >> 21;
    bits_1_through_10 &= 0b1111111111;
    bits_1_through_10 <<= 1;

    int32_t bit_11 = instruction >> 20;
    bit_11 &= 0b1;
    bit_11 <<= 11;

    int32_t bits_12_through_19 = instruction >> 12;
    bits_12_through_19 &= 0b11111111;
    bits_12_through_19 <<= 12;

    int32_t bit_20 = instruction >> 31;
    bit_20 <<= 20;

    int immediate_length = 21;
    int32_t immediate = bit_20 | bits_12_through_19 | bit_11 | bits_1_through_10;
    return immediate;
}



/*---------------------------------- Execute Immediate Select Unit -----------------------------------*/
int32_t (* immediate_formats[6]) (int32_t instruction) = {0};

void init_imm_sel_unit(void) {
    immediate_formats[0] = I_TYPE;
    immediate_formats[1] = I_STAR_TYPE;
    immediate_formats[2] = S_TYPE;
    immediate_formats[3] = B_TYPE;
    immediate_formats[4] = U_TYPE;
    immediate_formats[5] = J_TYPE;
}

void exec_imm_sel_unit(void) {
    int32_t instruction = IR.value;

    if (CONTROL_SIGNALS.ImmEn) {
        int32_t immediate = (immediate_formats[CONTROL_SIGNALS.ImmSel])(instruction);
        DATA_BUS = immediate;
    }
}
