
struct Buffer {
  uint32_t length;
  float *data;
};

struct Buffer newBufferWithMS(uint32_t ms);
struct Buffer newBufferWithFrames(uint32_t frames);
void deleteBuffer(struct Buffer *buffer);
