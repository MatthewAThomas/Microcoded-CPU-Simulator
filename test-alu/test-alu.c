#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

int32_t A_input;
int32_t B_input;
uint8_t ZERO_FLAG;

int32_t (* ALU_Ops[11]) (int32_t A_input, int32_t B_input);

int32_t COPY_A (int32_t A_input, int32_t B_input);
int32_t COPY_B (int32_t A_input, int32_t B_input);
int32_t INC_A_1 (int32_t A_input, int32_t B_input);
int32_t DEC_A_1 (int32_t A_input, int32_t B_input);
int32_t INC_A_4 (int32_t A_input, int32_t B_input);
int32_t DEC_A_4 (int32_t A_input, int32_t B_input);
int32_t ADD (int32_t A_input, int32_t B_input);
int32_t SUB (int32_t A_input, int32_t B_input);
int32_t SLT (int32_t A_input, int32_t B_input);
int32_t SLTU (int32_t A_input, int32_t B_input);
int32_t AND (int32_t A_input, int32_t B_input);

void init_alu_unit(void);


/*----------------------------------------------- TESTING COPY A -----------------------------------------------*/
int COPY_A_INDEX = 0;

void test_copy_a_1(void) {
    int32_t A_input = 42;
    int32_t B_input = 22;
    int32_t expected_result, returned_result;
    returned_result = (ALU_Ops[COPY_A_INDEX])(A_input, B_input);
    expected_result = 42;

    bool pass;
    pass = (returned_result == expected_result);
    pass &= (ZERO_FLAG == 0);
    if (pass) {
        printf("COPY_A test 1: PASS\n");
    } else {
        printf("COPY_A test 1: FAIL\n");
    }
}


/*----------------------------------------------- TESTING COPY B -----------------------------------------------*/
int COPY_B_INDEX = 1;

void test_copy_b_1(void) {
    int32_t A_input = 32;
    int32_t B_input = 0;
    int32_t expected_result, returned_result;
    returned_result = (ALU_Ops[COPY_B_INDEX])(A_input, B_input);
    expected_result = 0;

    bool pass;
    pass = (returned_result == expected_result);
    pass &= (ZERO_FLAG != 0);
    if (pass) {
        printf("COPY_B test 1: PASS\n");
    } else {
        printf("COPY_B test 1: FAIL\n");
    }
}


/*------------------------------------------------- TESTING SLT ---------------------------------------------------*/
int SLT_INDEX = 8;

void test_slt_1(void) {
    int32_t A_input = -1;
    int32_t B_input = 2;

    int32_t expected_result, returned_result;
    returned_result = (ALU_Ops[SLT_INDEX])(A_input, B_input);
    expected_result = (-1 < 2);

    bool pass;
    pass = (returned_result == expected_result);
    pass &= (ZERO_FLAG == 0);
    if (pass) {
        printf("SLT test 1: PASS\n");
    } else {
        printf("SLT test 1: FAIL\n");
    }
}

void test_slt_2(void) {
    int32_t A_input = -1;
    int32_t B_input = -3;

    int32_t expected_result, returned_result;
    returned_result = (ALU_Ops[SLT_INDEX])(A_input, B_input);
    expected_result = (-1 < -3);

    bool pass;
    pass = (returned_result == expected_result);
    pass &= (ZERO_FLAG != 0);
    if (pass) {
        printf("SLT test 2: PASS\n");
    } else {
        printf("SLT test 2: FAIL\n");
    }
}


/*----------------------------------------------------- TESTING SLTU -----------------------------------------------*/
int SLTU_INDEX = 9;

void test_sltu_1(void) {
    int32_t A_input = -1;
    int32_t B_input = 1;
    int32_t expected_result, returned_result;
    returned_result = (ALU_Ops[SLTU_INDEX])((unsigned) A_input, B_input);
    expected_result = 0;

    bool pass;
    pass = (returned_result == expected_result);
    pass &= (ZERO_FLAG != 0);
    if (pass) {
        printf("SLTU test 1: PASS\n");
    } else {
        printf("SLTU test 1: FAIL\n");
    }
}

int main(int argc, char **argv) {
    init_alu_unit();

    test_copy_a_1();
    printf("\n");

    test_copy_b_1();
    printf("\n");

    test_slt_1();
    test_slt_2();
    printf("\n");

    test_sltu_1();
    printf("\n");

    return 0;
}
