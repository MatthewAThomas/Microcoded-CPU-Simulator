#include "bus.h"
#include "call-functional-unit.h"
#include <stdio.h>

struct control_signals CONTROL_SIGNALS = {0};
int32_t DATA_BUS = 0;

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

void print_bus(void) {
    printf("Control signals:\n");
    printf("IRLd: %d\n ALUOp: %d\n ALd: %d\n BLd: %d\n RegSel: %d\n RegWr: %d\n \
            MALd: %d\n MemWr: %d\n MemEn: %d\n RegEn: %d\n ALUEn: %d\n ImmEn: %d\n ImmSel: %d\n",
            CONTROL_SIGNALS.IRLd, CONTROL_SIGNALS.ALUOp, CONTROL_SIGNALS.ALd,
            CONTROL_SIGNALS.BLd, CONTROL_SIGNALS.RegSel, CONTROL_SIGNALS.RegWr,
            CONTROL_SIGNALS.MALd, CONTROL_SIGNALS.MemWr, CONTROL_SIGNALS.MemEn,
            CONTROL_SIGNALS.RegEn, CONTROL_SIGNALS.ALUEn, CONTROL_SIGNALS.ImmEn,
            CONTROL_SIGNALS.ImmSel);
    
    printf("Data bus: (decimal) %d, (hex) %x\n", DATA_BUS, DATA_BUS);
}