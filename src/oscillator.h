#include "buffer.h"

#ifndef OSCILLATOR_H
#define OSCILLATOR_H

struct Oscillator {
  char name[8];
  struct Buffer wave;
  uint32_t (*render)(struct Oscillator, struct Buffer);
  void (*delete)(struct Oscillator *oscillator);
};

struct Oscillator newSinusOscillator();
uint32_t renderOscillatorToBuffer(struct Oscillator oscillator,
                                  struct Buffer buffer);
void deleteOscillator(struct Oscillator *oscillator);

#endif