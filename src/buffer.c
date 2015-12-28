#include <stdint.h>
#include "buffer.h"
#include "playback.h"



struct Buffer newBufferWithMS(uint32_t ms) {
    struct Buffer buffer;

    uint32_t length = (ms * SAMPLE_RATE) / 1000;

    if (ms > 60000) {
      buffer.data = NULL;
      buffer.length = 0;
      return buffer;
    }

    buffer.data = malloc(length * sizeof(float));
    buffer.length = (buffer.data != NULL) ? length : 0;

    return buffer;
}

void deleteBuffer(struct Buffer *buffer) {
    if (buffer->data) {
        free(buffer->data);
    }

    buffer->data = NULL;
    buffer->length = 0;
}
