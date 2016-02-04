#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "buffer.h"


unsigned long SAMPLE_RATE = 44100;

struct Buffer newBufferWithMS(uint32_t ms) {
    struct Buffer buffer;
    uint32_t length = (ms * SAMPLE_RATE) / 1000;

    if (ms > 60000) {
      buffer.data = NULL;
      buffer.length = 0;
      return buffer;
    }

    return newBufferWithFrames(length);
}

struct Buffer newBufferWithFrames(uint32_t frames) {
    struct Buffer buffer;

    if (frames > (60000 * SAMPLE_RATE)) {
      buffer.data = NULL;
      buffer.length = 0;
      return buffer;
    }

    buffer.data = malloc(frames * sizeof(float));
    buffer.length = (buffer.data != NULL) ? frames : 0;

    return buffer;
}

void deleteBuffer(struct Buffer *buffer) {
    if (buffer->data) {
        free(buffer->data);
    }

    buffer->data = NULL;
    buffer->length = 0;
}
