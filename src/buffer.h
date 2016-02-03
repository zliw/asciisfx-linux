#include <stddef.h>
#include <stdint.h>

#ifndef PARSER_H
#define PARSER_H

extern unsigned long SAMPLE_RATE;

struct Buffer {
  uint32_t length;
  float *data;
};

struct Buffer newBufferWithMS(uint32_t ms);
struct Buffer newBufferWithFrames(uint32_t frames);
void writeBufferToPath(struct Buffer buffer, const char* path);
void deleteBuffer(struct Buffer *buffer);

#endif