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

#define I_TYPE 0
#define I_STAR_TYPE 1
#define S_TYPE 2
#define B_TYPE 3
#define U_TYPE 4
#define J_TYPE 5

#define default 0
// INSERT NEW uOPS BEFORE NOP0. NOP0 SHOULD BE THE LAST LISTED uOP. FETCH0 SHOULD BE THE FIRST LISTED uOP
micro_op MICROCODE[] = {
    //    STATE       NEXT STATE      uBr          IRLd    RegSel   RegWr    RegEn     ALd      BLd     ALUOp    ALUEn    MALd     MemWr    MemEn      ImmSel     ImmEn      OPCODE    FUNCT3     FUNCT7
    {"FETCH0"      ,           "",          "N", {default,      PC,       0,       1,       1, default, default,       0,       1,       0,       0,     default,       0},         0,         0,         0},
                {"",           "",          "S", {      1, default,       0,       0,       0, default, default,       0,       0,       0,       1,     default,       0},         0,         0,         0},
                {"",           "",          "D", {      0,      PC,       1,       0,       0, default, INC_A_4,       1, default,       0,       0,     default,       0},         0,         0,         0},

    {"ADD"         ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0110011,         0,         0},
                {"",           "",          "N", {      0,     rs2,       0,       1,       0,       1, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,     ADD,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    {"SUB"         ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0110011,         0, 0b0100000},
                {"",           "",          "N", {      0,     rs2,       0,       1,       0,       1, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,     SUB,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    {"AND"         ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0110011,     0b111,         0},
                {"",           "",          "N", {      0,     rs2,       0,       1,       0,       1, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,     AND,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    {"OR"          ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0110011,     0b110,         0},
                {"",           "",          "N", {      0,     rs2,       0,       1,       0,       1, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,      OR,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    {"XOR"         ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0110011,     0b100,         0},
                {"",           "",          "N", {      0,     rs2,       0,       1,       0,       1, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,     XOR,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    {"SLL"         ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0110011,     0b001,         0},
                {"",           "",          "N", {      0,     rs2,       0,       1,       0,       1, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,     SLL,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    {"SRL"         ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0110011,     0b101,         0},
                {"",           "",          "N", {      0,     rs2,       0,       1,       0,       1, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,     SRL,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    {"SRA"         ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0110011,     0b101, 0b0100000},
                {"",           "",          "N", {      0,     rs2,       0,       1,       0,       1, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,     SRA,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    {"SLT"         ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0110011,     0b010,         0},
                {"",           "",          "N", {      0,     rs2,       0,       1,       0,       1, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,     SLT,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    {"SLTU"        ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0110011,     0b011,         0},
                {"",           "",          "N", {      0,     rs2,       0,       1,       0,       1, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,    SLTU,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    //    STATE       NEXT STATE      uBr          IRLd    RegSel   RegWr    RegEn     ALd      BLd     ALUOp    ALUEn    MALd     MemWr    MemEn      ImmSel     ImmEn      OPCODE    FUNCT3     FUNCT7
    {"ADDI"        ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0010011,         0,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       1, default,       0,       0,       0,       0,      I_TYPE,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,     ADD,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    {"ANDI"        ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0010011,     0b111,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       1, default,       0,       0,       0,       0,      I_TYPE,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,     AND,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    {"ORI"         ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0010011,     0b110,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       1, default,       0,       0,       0,       0,      I_TYPE,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,      OR,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    {"XORI"        ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0010011,     0b100,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       1, default,       0,       0,       0,       0,      I_TYPE,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,     XOR,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    {"SLLI"        ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0010011,     0b001,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       1, default,       0,       0,       0,       0, I_STAR_TYPE,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,     SLL,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    {"SRLI"        ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0010011,     0b101,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       1, default,       0,       0,       0,       0, I_STAR_TYPE,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,     SRL,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    {"SRAI"        ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0010011,     0b101, 0b0100000},
                {"",           "",          "N", {      0, default,       0,       0,       0,       1, default,       0,       0,       0,       0, I_STAR_TYPE,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,     SRA,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    {"SLTI"        ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0010011,     0b010,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       1, default,       0,       0,       0,       0,      I_TYPE,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,     SLT,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    {"SLTIU"       ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0010011,     0b011,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       1, default,       0,       0,       0,       0,      I_TYPE,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0,      rd,       1,       0,       0,       0,    SLTU,       1,       0,       0,       0,     default,       0},         0,         0,         0},

    //    STATE       NEXT STATE      uBr          IRLd    RegSel   RegWr    RegEn     ALd      BLd     ALUOp    ALUEn    MALd     MemWr    MemEn      ImmSel     ImmEn      OPCODE    FUNCT3     FUNCT7
    {"LW"          ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0000011,     0b010,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       1, default,       0,       0,       0,       0,      I_TYPE,       1},         0,         0,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       0,     ADD,       1,       1,       0,       0,     default,       0},         0,         0,         0},
                {"",           "",          "S", {      0,      rd,       1,       0,       0,       0, default,       0,       0,       0,       1,     default,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0, default,       0,       0,       0,       0, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},

    {"SW"          ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b0100011,     0b010,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       1, default,       0,       0,       0,       0,      S_TYPE,       1},         0,         0,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       0,     ADD,       1,       1,       0,       0,     default,       0},         0,         0,         0},
                {"",           "",          "S", {      0,     rs2,       0,       1,       0,       0, default,       0,       0,       1,       0,     default,       0},         0,         0,         0},
                {"",     "FETCH0",          "J", {      0, default,       0,       0,       0,       0, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},

    //    STATE       NEXT STATE      uBr          IRLd    RegSel   RegWr    RegEn     ALd      BLd     ALUOp    ALUEn    MALd     MemWr    MemEn      ImmSel     ImmEn      OPCODE    FUNCT3     FUNCT7
    {"BEQ"         ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b1100011,     0b000,         0},
                {"",           "",          "N", {      0,     rs2,       0,       1,       0,       1, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",   "_BEQ_RET",         "NZ", {      0, default,       0,       0,       0,       0,     SUB,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",           "",          "N", {      0,      PC,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       1, default,       0,       0,       0,       0,      B_TYPE,       1},         0,         0,         0},
                {"",           "",          "N", {      0,      PC,       1,       0,       0,       0,     ADD,       1,       0,       0,       0,     default,       0},         0,         0,         0},
        {"_BEQ_RET",     "FETCH0",          "J", {      0, default,       0,       0,       0,       0, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},

    {"BGE"         ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b1100011,     0b101,         0},
                {"",           "",          "N", {      0,     rs2,       0,       1,       0,       1, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",   "_BGE_RET",         "EZ", {      0, default,       0,       0,       0,       0,     SLT,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",           "",          "N", {      0,      PC,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       1, default,       0,       0,       0,       0,      B_TYPE,       1},         0,         0,         0},
                {"",           "",          "N", {      0,      PC,       1,       0,       0,       0,     ADD,       1,       0,       0,       0,     default,       0},         0,         0,         0},
        {"_BGE_RET",     "FETCH0",          "J", {      0, default,       0,       0,       0,       0, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},

    {"BGEU"        ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b1100011,     0b111,         0},
                {"",           "",          "N", {      0,     rs2,       0,       1,       0,       1, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",  "_BGEU_RET",         "EZ", {      0, default,       0,       0,       0,       0,    SLTU,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",           "",          "N", {      0,      PC,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       1, default,       0,       0,       0,       0,      B_TYPE,       1},         0,         0,         0},
                {"",           "",          "N", {      0,      PC,       1,       0,       0,       0,     ADD,       1,       0,       0,       0,     default,       0},         0,         0,         0},
       {"_BGEU_RET",     "FETCH0",          "J", {      0, default,       0,       0,       0,       0, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},

    {"BLT"         ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b1100011,     0b100,         0},
                {"",           "",          "N", {      0,     rs2,       0,       1,       0,       1, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",   "_BLT_RET",         "NZ", {      0, default,       0,       0,       0,       0,     SLT,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",           "",          "N", {      0,      PC,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       1, default,       0,       0,       0,       0,      B_TYPE,       1},         0,         0,         0},
                {"",           "",          "N", {      0,      PC,       1,       0,       0,       0,     ADD,       1,       0,       0,       0,     default,       0},         0,         0,         0},
        {"_BLT_RET",     "FETCH0",          "J", {      0, default,       0,       0,       0,       0, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},

    {"BLTU"        ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b1100011,     0b110,         0},
                {"",           "",          "N", {      0,     rs2,       0,       1,       0,       1, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",  "_BLTU_RET",         "NZ", {      0, default,       0,       0,       0,       0,    SLTU,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",           "",          "N", {      0,      PC,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       1, default,       0,       0,       0,       0,      B_TYPE,       1},         0,         0,         0},
                {"",           "",          "N", {      0,      PC,       1,       0,       0,       0,     ADD,       1,       0,       0,       0,     default,       0},         0,         0,         0},
       {"_BLTU_RET",     "FETCH0",          "J", {      0, default,       0,       0,       0,       0, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},

    {"BNE"         ,           "",          "N", {      0,     rs1,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0}, 0b1100011,     0b001,         0},
                {"",           "",          "N", {      0,     rs2,       0,       1,       0,       1, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",   "_BNE_RET",         "EZ", {      0, default,       0,       0,       0,       0,     SUB,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",           "",          "N", {      0,      PC,       0,       1,       1,       0, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},
                {"",           "",          "N", {      0, default,       0,       0,       0,       1, default,       0,       0,       0,       0,      B_TYPE,       1},         0,         0,         0},
                {"",           "",          "N", {      0,      PC,       1,       0,       0,       0,     ADD,       1,       0,       0,       0,     default,       0},         0,         0,         0},
        {"_BNE_RET",     "FETCH0",          "J", {      0, default,       0,       0,       0,       0, default,       0,       0,       0,       0,     default,       0},         0,         0,         0},


    {"NOP0"        ,      "FETH0",          "J", { default, default,      0,       0, default, default, default,       0, default,       0,       0,     default,       0},         0,         0,         0}
};

    //{"          ", "          ", "          ", {       ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,            ,        },          ,          ,          },
    //          {"",           "",           "", {       ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,            ,        },          ,          ,          },