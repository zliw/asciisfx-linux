#include <stddef.h>
#include <stdint.h>

#ifndef BUFFER_H
#define BUFFER_H

extern unsigned long SAMPLE_RATE;

struct Buffer {
  uint32_t length;  //length in samples/floats
  float *data;
};

struct BufferOperation {
  char name[8];
  struct Buffer wave;
  uint16_t length_in_ms;
  uint16_t is_generator;
  uint32_t (*render)(struct BufferOperation, struct Buffer);
  void (*delete)(struct BufferOperation *oscillator);
};

typedef struct BufferOperation BufferOperation;
typedef struct Buffer Buffer;

Buffer newBufferWithMS(uint32_t ms);
Buffer newBufferWithFrames(uint32_t frames);
void writeBufferToPath(Buffer buffer, const char* path);
void deleteBuffer(Buffer *buffer);

#endif