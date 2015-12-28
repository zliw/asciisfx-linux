
struct Buffer {
  uint32_t length;
  float *data;
};

struct Buffer newBufferWithMS(uint32_t ms);
void deleteBuffer(struct Buffer *buffer);
