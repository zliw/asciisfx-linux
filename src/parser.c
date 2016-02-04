#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "oscillator.h"

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
        case 'S':
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
