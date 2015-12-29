#include "playback.h"
#include "buffer.h"

struct Oscillator {
  struct Buffer wave;
};

struct Oscillator newSinusOscillator();
void renderOscillatorToBuffer(struct Oscillator oscillator,
                              struct Buffer buffer);
void deleteOscillator(struct Oscillator *oscillator);
