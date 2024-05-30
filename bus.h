#include <stdint.h>

int32_t DATA_BUS;

struct control_signals {
    uint8_t IRLd;
    uint8_t ALUOp;
    uint8_t ALd;
    uint8_t BLd;
    uint8_t RegSel;
    uint8_t RegWr;
    uint8_t MALd;
    uint8_t MemWr;
    uint8_t MemEn;
    uint8_t RegEn;
    uint8_t ALUEn;
    uint8_t ImmEn;
    uint8_t ImmSel;
};
struct control_signals CONTROL_SIGNALS;

/* Initialize bus data structures. Return NULL if not succesful */
// void init_control_bus(void);