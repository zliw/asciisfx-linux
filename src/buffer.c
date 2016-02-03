#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <sndfile.h>

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

void writeBufferToPath(struct Buffer buffer, const char* path) {
    SF_INFO sfinfo;
    sfinfo.channels = 1;
    sfinfo.samplerate = SAMPLE_RATE;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    SNDFILE * outfile = sf_open(path, SFM_WRITE, &sfinfo);
    sf_count_t count = sf_write_float(outfile, buffer.data, buffer.length);
    sf_write_sync(outfile);
    sf_close(outfile);
}

void deleteBuffer(struct Buffer *buffer) {
    if (buffer->data) {
        free(buffer->data);
    }

    buffer->data = NULL;
    buffer->length = 0;
}
