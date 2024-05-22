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



/*----------------------------------------- TESTING I STAR TYPE INSTRUCTIONS ------------------------------------*/
int32_t make_i_star_type_instruction(int32_t immediate) {
    immediate <<= 20;
    int32_t instruction = immediate;
    return instruction;
}

// make sure i star type instruction immediates are unsigned
void test_i_star_type_1(void) {
    int32_t immediate = 0b11111;
    int32_t instruction = make_i_star_type_instruction(immediate);
    int32_t expected_immediate, returned_immediate;
    returned_immediate = I_STAR_TYPE(instruction);
    expected_immediate = 0b11111;
    bool pass = (expected_immediate == returned_immediate);

    if (pass) {
        printf("I Star type test 1: PASS\n");
    } else {
        printf("I Star type test 1: FAIL\n");
    }
}



/*----------------------------------------------------- TESTING S TYPE INSTRUCTIONS ----------------------------------------*/
int32_t make_s_type_instruction(int32_t upper, int32_t lower) {
    upper <<= 25;
    lower <<= 7;
    int32_t instruction = upper + lower;
    return instruction;
}

// basic test
void test_s_type_1(void) {
    int32_t upper = 0b0000001;
    int32_t lower = 0b00001;
    int32_t instruction = make_s_type_instruction(upper, lower);
    int32_t expected_immediate, returned_immediate;
    returned_immediate = S_TYPE(instruction);
    expected_immediate = 0b000000100001;
    bool pass = (expected_immediate == returned_immediate);

    if (pass) {
        printf("S type test 1: PASS\n");
    } else {
        printf("S type test 1: FAIL\n");
    }
}

// make sure that immediate is sign extended
void test_s_type_2(void) {
    int32_t upper = 0b1111111;
    int32_t lower = 0b11111;
    int32_t instruction = make_s_type_instruction(upper, lower);
    int32_t expected_immediate, returned_immediate;
    returned_immediate = S_TYPE(instruction);
    expected_immediate = -1;
    bool pass = (expected_immediate == returned_immediate);

    if (pass) {
        printf("S type test 2: PASS\n");
    } else {
        printf("S type test 2: FAIL\n");
    }
}



/*---------------------------------------------------- TESTING B TYPE INSTRUCTIONS -----------------------------------------*/

int32_t make_b_type_instruction(int32_t twelfth, int32_t eleventh, int32_t ten_thru_five, int32_t four_thru_one) {
    twelfth <<= 31;
    eleventh <<= 7;
    ten_thru_five <<= 25;
    four_thru_one <<= 8;

    int32_t instruction = twelfth | eleventh | eleventh | ten_thru_five | four_thru_one;
    return instruction;
}

void test_b_type_1(void) {
    int32_t twelfth = 1;
    int32_t eleventh = 1;
    int32_t ten_thru_five = 0b111111;
    int32_t four_thru_one = 0b1111;
    int32_t instruction = make_b_type_instruction(twelfth, eleventh, ten_thru_five, four_thru_one);

    int32_t expected_immediate, returned_immediate;
    returned_immediate = B_TYPE(instruction);
    expected_immediate = -2;
    bool pass = (returned_immediate == expected_immediate);

    if (pass) {
        printf("B type test 1: PASS\n");
    } else {
        printf("B type test 1: FAIL\n");
    }
}

void test_b_type_2(void) {
    int32_t twelfth = 0;
    int32_t eleventh = 1;
    int32_t ten_thru_five = 0b111111;
    int32_t four_thru_one = 0b1111;
    int32_t instruction = make_b_type_instruction(twelfth, eleventh, ten_thru_five, four_thru_one);

    int32_t expected_immediate, returned_immediate;
    returned_immediate = B_TYPE(instruction);
    expected_immediate = 2047 * 2;
    bool pass = (returned_immediate == expected_immediate);

    if (pass) {
        printf("B type test 2: PASS\n");
    } else {
        printf("B type test 2: FAIL\n");
    }
}



/*------------------------------------------------ TESTING U TYPE INSTRUCTIONS -----------------------------------------------*/
int32_t make_u_type_instruction(int32_t immediate) {
    immediate <<= 12;
    int32_t instruction = immediate;
    return instruction;
}

void test_u_type_1(void) {
    int32_t immediate = 0b11111111111111111111;
    int32_t instruction = make_u_type_instruction(immediate);
    int32_t expected_immediate, returned_immediate;
    returned_immediate = U_TYPE(instruction);
    expected_immediate = -1 << 12;
    bool pass = (returned_immediate == expected_immediate);

    if (pass) {
        printf("U type test 1: PASS\n");
    } else {
        printf("U type test 1: FAIL\n");
    }
}

void test_u_type_2(void) {
    int32_t immediate = 0b01010101010101010101;
    int32_t instruction = make_u_type_instruction(immediate);
    int32_t expected_immediate, returned_immediate;
    returned_immediate = U_TYPE(instruction);
    expected_immediate = 0b01010101010101010101 << 12;
    bool pass = (returned_immediate == expected_immediate);

    if (pass) {
        printf("U type test 2: PASS\n");
    } else {
        printf("U type test 2: FAIL\n");
    }
}


/*------------------------------------------------ TESTING J TYPE INSTRUCTIONS ----------------------------------------------*/

int32_t make_j_type_instruction(int32_t twentieth, int32_t nineteen_thru_twelve, int32_t eleventh, int32_t ten_thru_one) {
    twentieth <<= 31;
    nineteen_thru_twelve <<= 12;
    eleventh <<= 20;
    ten_thru_one <<= 21;
    int32_t instruction = twentieth | nineteen_thru_twelve | eleventh | ten_thru_one;
    return instruction;
}

void test_j_type_1(void) {
    int32_t twentieth = 0;
    int32_t nineteen_thru_twelve = 0b11111111;
    int32_t eleventh = 0;
    int32_t ten_thru_one = 0b1111111111;
    int32_t instruction = make_j_type_instruction(twentieth, nineteen_thru_twelve, eleventh, ten_thru_one);
    int32_t expected_immediate, returned_immediate;
    returned_immediate = J_TYPE(instruction);
    expected_immediate = 0b01111111101111111111 << 1;
    bool pass = (returned_immediate == expected_immediate);

    if (pass) {
        printf("J type test 1: PASS\n");
    } else {
        printf("J type test 1: FAIL\n");
    }
}

void test_j_type_2(void) {
    int32_t twentieth = 1;
    int32_t nineteen_thru_twelve = 0b11111111;
    int32_t eleventh = 1;
    int32_t ten_thru_one = 0b1111111111;
    int32_t instruction = make_j_type_instruction(twentieth, nineteen_thru_twelve, eleventh, ten_thru_one);
    int32_t expected_immediate, returned_immediate;
    returned_immediate = J_TYPE(instruction);
    expected_immediate = -2;
    bool pass = (returned_immediate == expected_immediate);

    if (pass) {
        printf("J type test 2: PASS\n");
    } else {
        printf("J type test 2: FAIL\n");
    }
}



// test main
int main(int argc, char **argv) {
    test_i_type_1();
    test_i_type_2();
    test_i_type_3();
    test_i_type_4();
    printf("\n");

    test_i_star_type_1(); 
    printf("\n");

    test_s_type_1();
    test_s_type_2();
    printf("\n");

    test_b_type_1();
    test_b_type_2();
    printf("\n");

    test_u_type_1();
    test_u_type_2();
    printf("\n");

    test_j_type_1();
    test_j_type_2();
    printf("\n");

    return 0;
}