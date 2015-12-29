#include "oscillator.h"

struct Oscillator newSinusOscillator() {
    struct Oscillator oscillator;
    oscillator.wave = newBufferWithFrames(1024);
    return oscillator;
}

void renderOscillatorToBuffer(struct Oscillator oscillator,
                              struct Buffer buffer) {
}

void deleteOscillator(struct Oscillator *oscillator) {
    deleteBuffer(&oscillator->wave);
}
