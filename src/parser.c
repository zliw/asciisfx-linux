#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "oscillator.h"


uint32_t parse_integer(const char* string, uint16_t *value) {
    uint32_t index = 0;

    *value = 0;

    while (index < strlen(string)) {
        char c = string[index];

        if ((c >= '0') && (c <= '9')) {
            uint32_t v = c - '0';

            if (value == 0) {
                *value = v;
            } else {
                *value = *value * 10 + v;
            }
            index++;
        }
        else {
            break;
        }
    }
    return index;
}


uint32_t parse_notes(const char*string, Note **sequence) {

    uint32_t index = 0;
    uint8_t octave = 4;
    uint8_t is_slide = 0;
    Note note;

    *sequence = NULL;

    while (index < strlen(string)) {
        char c = string[index];
        if ((c >= '0') && (c <= '9')) {
            note.length = c - '0';
        }
        else if ((c >= 'a') && (c <= 'g')) {
        }
        else if (c == '.') {
            
        }
        else if (c == '/') {
            is_slide = 1;
        }
        else if (c == '+') {
            
        }
        else if (c == '-') {
            
        }
        else {
            return index;
        }

        index++;
    }

    return index;
}


BufferOperation *parse(const char* command) {
    BufferOperation *operations = malloc(sizeof(BufferOperation) * 2);
    uint32_t index = 0;
    uint32_t operation_index = 0;

    while (index < strlen(command)) {
      char current = command[index];

      fprintf(stderr, "found character '%c'\n", current);
      switch (current) {
        case 0:
            break;
        case 'S': {
            BufferOperation operation;

            index++;
            switch(command[index]) {
                case 'I': {
                    operation = newSinusOscillator();
                    break;
                }
                case 'Q': {
                    operation = newSquareOscillator();
                    break;
                }
                default:
                    goto ERROR;
            }

            uint16_t duration = 0;
            uint32_t offset = parse_integer(&command[index + 1], &duration);
            index += offset + 1;

            Note *sequence = NULL;
            index += parse_notes(&command[index], &sequence);

            operation.length_in_ms = duration;
            operations[operation_index++] = operation;

            break;
        }
        default:
            goto ERROR;
      }
    }

    return operations;
ERROR:
    fprintf(stderr, "parse error at index %d: \n", index);
    char current = command[index];
    if (current == 0) {
        fprintf(stderr, "unexpected end of command\n");
    }
    else {
        fprintf(stderr, "unexpected character: '%c'\n", current);
    }

    free(operations);
    return NULL;
}
