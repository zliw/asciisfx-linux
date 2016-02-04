#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "buffer.h"

BufferOperation newSinusOscillator();
uint32_t renderOscillatorToBuffer(BufferOperation oscillator,
                                  Buffer buffer);
void deleteOscillator(BufferOperation *oscillator);

#endif