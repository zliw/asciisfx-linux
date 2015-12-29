#include <stdio.h>
#include <stdlib.h>

#include "arguments.h"
#include "playback.h"
#include "oscillator.h"

int main(int argc, char *argv[]) {
    struct ProcessOptions options = parse_command_line(argc, argv);

    struct Buffer buffer = newBufferWithMS(1000);
    struct Oscillator oscillator = newSinusOscillator();

    renderOscillatorToBuffer(oscillator, buffer);

    play(buffer);

    return 0;
}
