#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "buffer.h"

struct Note {
    char note;
    uint8_t octave;
    uint8_t length;
    char to_note;
    uint8_t to_octave;
};

typedef struct Note Note;

BufferOperation newSinusOscillator();
BufferOperation newSquareOscillator();
uint32_t renderOscillatorToBuffer(BufferOperation oscillator,
                                  Buffer buffer);
void deleteOscillator(BufferOperation *oscillator);

#endif