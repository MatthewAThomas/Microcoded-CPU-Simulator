#include "loader.h"
#include <stdio.h>
#include <ctype.h>

/* Programs assumed to be written in machine code to a text file. More details in README */

#define MAX_LINE_SIZE 12


bool load_line(uint8_t *memory_pointer, char *line) {
    if (line[0] == '#')
        return true;
    
    int hex_digit_count = 0;
    for (int i = 0; i < MAX_LINE_SIZE; i++, line++) {
        char character = *line;

        if (character == '#')
            return (hex_digit_count == 8);

        if ((!isxdigit(character)) && (!isspace(character)))
            return false;

        if (isspace(character))
            continue;

        if (isalpha(character))
            character = tolower(character);
        *line = character;
        hex_digit_count++;
    }

    return (hex_digit_count == 8);
}

/* Returns true if program succesfully loaded. False otherwise. */
bool load(uint8_t *memory_pointer) {
    FILE *file_pointer;

    /* Set the path of the program to be loaded here */
    char *program = "./programs/test1.txt";
    file_pointer = fopen(program, "r");
    if (file_pointer == NULL) {
        printf("Program %s does not exist\n", program);
        fclose(file_pointer);
        return false;
    }

    char line[MAX_LINE_SIZE];
    int line_number = 0;

    while (fgets(line, MAX_LINE_SIZE, file_pointer)) {
        bool valid_line = load_line(memory_pointer, line);
        if (valid_line == false) {
            printf("Loading Error: formatting issue on line %d", line_number);
            fclose(file_pointer);
            return false;
        }

        line_number++;
        memory_pointer += 4;
    }

    fclose(file_pointer);
    return true;
}