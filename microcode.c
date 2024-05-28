/*
Contains the microcode "ROM"
"FETCH0" is assumed to be the first micro-op in the ROM
"NOP0" is assumed to be the last micro-op in the ROM
*/


#include "microcode.h"
#include <stdint.h>

#define PC 0
#define RA 1
#define rd 2
#define rs1 3
#define rs2 4

#define COPY_A 0
#define COPY_B 1
#define INC_A_1 2
#define DEC_A_1 3
#define INC_A_4 4
#define DEC_A_4 5
#define ADD 6
#define SUB 7
#define SLT 8
#define SLTU 9
#define AND 10
#define OR 11
#define XOR 12
#define SLL 13
#define SRL 14
#define SRA 15

#define default 0
// INSERT NEW uOPS BEFORE NOP0. NOP0 SHOULD BE THE LAST LISTED uOP. FETCH0 SHOULD BE THE FIRST LISTED uOP
micro_op MICROCODE[] = {
    //    STATE       NEXT STATE      uBr          IRLd    RegSel   RegWr    RegEn     ALd      BLd     ALUOp    ALUEn    MALd     MemWr    MemEn    ImmSel   ImmEn       OPCODE
    {"FETCH0"      ,           "",          "N", {default,      PC,       0,       1,       1, default, default,       0,       1,       0,       0, default,       0},            0},
                {"",           "",          "S", {      1, default,       0,       0,       0, default, default,       0,       0,       0,       1, default,       0},            0},
                {"",           "",          "D", {      0,      PC,       1,       0,       0, default, INC_A_4,       1, default,       0,       0, default,       0},            0},

    {"NOP0"        ,      "FETH0",          "J", { default, default,      0,       0, default, default, default,       0, default,       0,       0, default,       0},            0}
};

    //{"          ", "          ", "          ", {       ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        }}
    //                              {"", "", "", {       ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        }}
