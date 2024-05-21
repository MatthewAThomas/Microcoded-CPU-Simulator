#include "decode.h"
#include <stdint.h>

/* 0 -> PC, 1 -> RA, 2 -> rd, 3 -> rs1, 4 -> rs2 */
uint8_t REGISTER_FILE_MUX[5] = {32, 1, 0, 0, 0};
