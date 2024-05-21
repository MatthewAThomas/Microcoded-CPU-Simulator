#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

int32_t I_TYPE (int32_t instruction);
int32_t I_STAR_TYPE (int32_t instruction);
int32_t S_TYPE (int32_t instruction);
int32_t B_TYPE (int32_t instruction);
int32_t U_TYPE (int32_t instruction);
int32_t J_TYPE (int32_t instruction);
int32_t sign_extend(int immediate_length, int32_t unprocessed_imm);
void init_imm_sel_unit(void);



/* ------------------------------------------ TESTING I TYPES -------------------------------------------------*/
int32_t make_i_type_instruction(int32_t funct3, int32_t immediate) {
    int32_t opcode = 0b0010011;
    funct3 <<= 12;
    immediate <<= 20;
    int32_t instruction = immediate + funct3 + opcode;
    return instruction;
}

// andi: rd = 0, rs1 = 0, imm = 1
void test_i_type_1 (void) {
    int32_t funct3 = 0b111;
    int32_t immediate = 1;
    int32_t instruction = make_i_type_instruction(funct3, immediate);
    int32_t expected_immediate, returned_immediate;
    returned_immediate = I_TYPE(instruction);
    expected_immediate = 1;
    bool pass = (expected_immediate == returned_immediate);

    if (pass) {
        printf("I type test 1: PASS\n");
    } else {
        printf("I type test 1: FAIL\n");
    }
}

// andi: rd = 0, rs1 = 0, imm = -1
// test sign_extend
void test_i_type_2 (void) {
    int32_t funct3 = 0b111;
    int32_t immediate = 0b111111111111;
    int32_t instruction = make_i_type_instruction(funct3, immediate);
    int32_t expected_immediate, returned_immediate;
    returned_immediate = I_TYPE(instruction);
    expected_immediate = -1;
    bool pass = (expected_immediate == returned_immediate);

    if (pass) {
        printf("I type test 2: PASS\n");
    } else {
        printf("I type test 2: FAIL\n");
    }
}

// andi: rd = 0, rs1 = 0, imm = -2048
// further testing sign_extend
void test_i_type_3 (void) {
    int32_t funct3 = 0b111;
    int32_t immediate = 0b100000000000;
    int32_t instruction = make_i_type_instruction(funct3, immediate);
    int32_t expected_immediate, returned_immediate;
    returned_immediate = I_TYPE(instruction);
    expected_immediate = -2048;
    bool pass = (expected_immediate == returned_immediate);

    if (pass) {
        printf("I type test 3: PASS\n");
    } else {
        printf("I type test 3: FAIL\n");
    }
}

// sltiu: rd = 0, rs1 = 0, imm = -1
// making sure sltiu is not sign extended
void test_i_type_4 (void) {
    int32_t funct3 = 0b011;
    int32_t immediate = 0b111111111111;
    int32_t instruction = make_i_type_instruction(funct3, immediate);
    int32_t expected_immediate, returned_immediate;
    returned_immediate = I_TYPE(instruction);
    expected_immediate = 4095;
    bool pass = (expected_immediate == returned_immediate);

    if (pass) {
        printf("I type test 4: PASS\n");
    } else {
        printf("I type test 4: FAIL\n");
    }
}

// test main
int main(int argc, char **argv) {
    test_i_type_1();
    test_i_type_2();
    test_i_type_3();
    test_i_type_4(); 
    return 0;
}