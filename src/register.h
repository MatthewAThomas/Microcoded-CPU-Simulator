#include <stdint.h>

struct Register {
    int32_t value;
    uint8_t *Ld_Wr;  // load or write signal
};

struct Register IR;
struct Register A;
struct Register B;
struct Register MA;

void print_registers(void);