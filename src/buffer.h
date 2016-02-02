#include <stddef.h>
#include <stdint.h>


#define SAMPLE_RATE 44100 

struct Buffer {
  uint32_t length;
  float *data;
};

struct Buffer newBufferWithMS(uint32_t ms);
struct Buffer newBufferWithFrames(uint32_t frames);
void writeBufferToPath(struct Buffer buffer, const char* path);
void deleteBuffer(struct Buffer *buffer);
