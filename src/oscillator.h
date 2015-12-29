#include "playback.h"
#include "buffer.h"

struct Oscillator {
  struct Buffer wave;
};

struct Oscillator newSinusOscillator();
uint32_t renderOscillatorToBuffer(struct Oscillator oscillator,
                                  struct Buffer buffer);
void deleteOscillator(struct Oscillator *oscillator);
