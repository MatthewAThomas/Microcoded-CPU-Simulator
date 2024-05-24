#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define MEM_SIZE 1024
uint8_t MEMORY[MEM_SIZE];

bool load(uint8_t *memory_pointer, int max_size);

int main(int argc, char **argv) {
    // change depending on the program being loaded (set in loader.c)
    int max_size = 28;
    load(MEMORY, max_size);
    for (int i = 0; i < max_size; i++) {
        printf("%x", MEMORY[i]);
        if (i % 4 == 3)
            printf("\n");
    }
}

