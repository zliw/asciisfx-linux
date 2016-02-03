#include <stdlib.h>
#include <stdio.h>

#include "parser.h"
#include "oscillator.h"

struct Oscillator *parse(const char* command) {
    struct Oscillator *operations = malloc(sizeof(struct Oscillator) * 2);
    uint32_t index = 0;
    uint32_t operation_index = 0;

    while (index < strlen(command)) {
      char current = command[index];

      switch (current) {
        case 0:
            break;
        case 'S':
            fprintf(stderr, "found character %c\n", current);
            operations[operation_index] = newSinusOscillator();
            operation_index++;
            break;
        default:
        free(operations);
            return NULL;
      }
      index++;
    }

    return operations;
}
