#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>
#include <stdbool.h>

uint8_t REGISTER_FILE_MUX[5];

bool init_ucode_engine(void);
int exec_ucode_engine(void);

#endif // ENGINE_H