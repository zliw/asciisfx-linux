#include <math.h>
#include "oscillator.h"

struct Oscillator newSinusOscillator() {
    struct Oscillator oscillator;
    oscillator.wave = newBufferWithFrames(1024);

    float *data = oscillator.wave.data;
    float length = (float) oscillator.wave.length;
    uint32_t i;

    for (i = 0; i < oscillator.wave.length; i++) {
        data[i] = sinf(((float) i) / length * 2 * M_PI);
    }

    return oscillator;
}

void renderOscillatorToBuffer(struct Oscillator oscillator,
                              struct Buffer buffer) {
}

void deleteOscillator(struct Oscillator *oscillator) {
    deleteBuffer(&oscillator->wave);
}
