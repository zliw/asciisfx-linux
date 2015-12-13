#include <stdio.h>
#include <stdlib.h>
#include "arguments.h"

int main(int argc, char *argv[]) {
    struct ProcessOptions options = parse_command_line(argc, argv);
    return 0;
}
