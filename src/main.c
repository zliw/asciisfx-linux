#include <stdio.h>
#include <stdlib.h>

#include "arguments.h"
#include "oscillator.h"
#include "parser.h"

int main(int argc, char *argv[]) {
    struct ProcessOptions options = parse_command_line(argc, argv);

    Buffer buffer = newBufferWithMS(1000);
    BufferOperation oscillator = newSinusOscillator();

    oscillator.render(oscillator, buffer);

    writeBufferToPath(buffer, options.output_filename);

    oscillator.delete(&oscillator);

    return 0;
}
