#include <alsa/asoundlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PCM_DEVICE "default"
#define SAMPLE_RATE 44100

struct Buffer;
uint32_t play(struct Buffer buffer);
