#include <stdio.h>
#include <stdlib.h>

#include "arguments.h"
#include "oscillator.h"

int main(int argc, char *argv[]) {
    struct ProcessOptions options = parse_command_line(argc, argv);

    struct Buffer buffer = newBufferWithMS(1000);
    struct Oscillator oscillator = newSinusOscillator();

    renderOscillatorToBuffer(oscillator, buffer);

    writeBufferToPath(buffer, options.output_filename);

    return 0;
}
