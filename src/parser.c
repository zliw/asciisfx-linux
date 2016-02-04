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
            index++;
            switch(command[index]) {
                case 'I':
                    operations[operation_index] = newSinusOscillator();
                    break;
                default:
                    goto ERROR;
            }

            index++;
            operation_index++;
            break;
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
