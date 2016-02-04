#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "oscillator.h"

uint32_t renderOscillatorToBuffer(BufferOperation self,
                                  Buffer buffer) {

    if (buffer.length == 0) {
        return 0;
    }

    if (buffer.data == NULL) {
        return 0;
    }

    //frequencyBuffer.render()

    //let frequency = frequencyBuffer.buffer.floatChannelData[0]
    //let volumes = frequencyBuffer.volumeBuffer.buffer.floatChannelData[0]
    uint32_t i;
    float phase = 0.0;
    float volume = 1.0;
    float value;
    float f = 220.0;

    // only fill up to buffer length. if self.length is shorter only fill there
    uint32_t max = buffer.length;
    uint32_t length = self.length_in_ms * SAMPLE_RATE / 1000;
    max = (max < length) ? max : length;

    for (i = 0; i < max; i++) {
        //f = frequency[i];
        if (f == 0) {
            buffer.data[i] = 0;
        }
        else {
            phase +=  self.wave.length * f / SAMPLE_RATE;
            // let volume = volumes[i]
            value = volume * self.wave.data[((int) phase) % self.wave.length];
            buffer.data[i] = value;
        }
    }

    return 1;
}


void deleteOscillator(BufferOperation *oscillator) {
    deleteBuffer(&oscillator->wave);
}


BufferOperation newWavetableOscillator() {
    BufferOperation oscillator;

    oscillator.length_in_ms = 100;
    oscillator.is_generator = 1;
    oscillator.wave = newBufferWithFrames(1024);
    oscillator.render = renderOscillatorToBuffer;
    oscillator.delete = deleteOscillator;

    return oscillator;
}


BufferOperation newSinusOscillator() {
    BufferOperation oscillator = newWavetableOscillator();

    strncpy(oscillator.name, "sinus", 8);

    float *data = oscillator.wave.data;
    float length = (float) oscillator.wave.length;
    uint32_t i;

    for (i = 0; i < oscillator.wave.length; i++) {
        data[i] = sinf(((float) i) / length * 2 * M_PI);
    }

    return oscillator;
}


BufferOperation newSquareOscillator() {
    BufferOperation oscillator = newWavetableOscillator();

    strncpy(oscillator.name, "square", 8);

    float *data = oscillator.wave.data;
    float length = (float) oscillator.wave.length;
    uint32_t i;

    for (i = 0; i < oscillator.wave.length / 2; i++) data[i] = 1;
    for (i; i < oscillator.wave.length; i++) data[i] = -1;

    return oscillator;
}
