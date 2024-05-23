#include "loader.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Programs assumed to be written in machine code to a text file. More details in README */

#define MAX_LINE_SIZE 12

// each line represents 4 bytes of memory
#define MAX_NUM_LINES(MAX_SIZE) (MAX_SIZE / 4)

uint8_t hex_to_bin(char character) {
    switch(character) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case 9:
            return 9;
        case 'A':
        case 'a':
            return 10;
        case 'B':
        case 'b':
            return 11;
        case 'C':
        case 'c':
            return 12;
        case 'D':
        case 'd':
            return 13;
        case 'E':
        case 'e':
            return 14;
        case 'F':
        case 'f':
            return 15;
    }
}

bool load_line(uint8_t *memory_pointer, char *line) {
    if (line[0] == '\n')
        return true;
    
    if (line[0] == '#')
        return true;
    
    int hex_digit_count = 0;
    for (int i = 0; i < MAX_LINE_SIZE; i++, line++) {
        char character = *line;

        if (character == '#')
            return (hex_digit_count == 8);

        if ((!isxdigit(character)) && (!isspace(character)))
            return (hex_digit_count == 8);

        if (isspace(character))
            continue;

        uint8_t nibble = hex_to_bin(character);
        nibble = (hex_digit_count % 2 == 0) ? (nibble << 4) : nibble;

        *memory_pointer |= nibble;
        memory_pointer = (hex_digit_count % 2) ? (memory_pointer + 1) : memory_pointer;

        hex_digit_count++;
    }

    return (hex_digit_count == 8);
}

/* Returns true if program succesfully loaded. False otherwise. */
bool load(uint8_t *memory_pointer, int max_size) {
    FILE *file_pointer;

    /* Set the path of the program to be loaded here */
    char program_dir_path[4096] = "/home/projects/ucoded-processor/programs/";
    char *program = "test1.txt";
    file_pointer = fopen(strcat(program_dir_path, program), "r");
    if (file_pointer == NULL) {
        printf("Program %s does not exist\n", program);
        return false;
    }

    int max_num_lines = MAX_NUM_LINES(max_size);
    char line[MAX_LINE_SIZE];
    int line_number = 0;

    while (fgets(line, MAX_LINE_SIZE, file_pointer)) {
        // if (line_number >= max_num_lines) {
        //     printf("Loading Error: the program is larger than the current size of memory (%d bytes)\n", max_size);
        //     fclose(file_pointer);
        //     return false;
        // }

        bool valid_line = load_line(memory_pointer, line);
        if (valid_line == false) {
            printf("Loading Error: formatting issue on line %d\n", line_number);
            fclose(file_pointer);
            return false;
        }

        line_number++;
        memory_pointer += 4;
    }

    fclose(file_pointer);
    return true;
}