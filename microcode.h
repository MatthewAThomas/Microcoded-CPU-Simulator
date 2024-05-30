#include <stdint.h>

#define NUM_LABELED_STATES 3

#define MICROCODE_WIDTH 13

#define STATE_IDENTIFIER_LENGTH 11
typedef struct {
    char state[STATE_IDENTIFIER_LENGTH];
    char next_state[STATE_IDENTIFIER_LENGTH];
    char uBr[3];
    uint8_t control_signals[MICROCODE_WIDTH];
    uint8_t opcode;
} micro_op;

micro_op MICROCODE[];