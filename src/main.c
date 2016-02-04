#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sndfile.h>

#include "arguments.h"
#include "oscillator.h"
#include "parser.h"


uint16_t file_exists(const char * path) {
   struct stat buffer;
   int i = stat(path, &buffer);
   return (i == 0);
}


void writeBufferToPath(struct Buffer buffer, const char* path) {
    SF_INFO sfinfo;
    sfinfo.channels = 1;
    sfinfo.samplerate = SAMPLE_RATE;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    if (file_exists(path)) {
        remove(path);
    }

    SNDFILE * outfile = sf_open(path, SFM_WRITE, &sfinfo);
    sf_count_t count = sf_write_float(outfile, buffer.data, buffer.length);
    sf_write_sync(outfile);
    sf_close(outfile);
}



uint16_t get_maximum_length(BufferOperation *operations) {
    uint32_t index = 0;
    uint16_t max = 0;

    while (operations[index].name[0] != 0) {
        BufferOperation operation = operations[index];
        max = (operation.length_in_ms > max) ? operation.length_in_ms : max;
        index++;
    }

    return max;
}


Buffer render(BufferOperation *operations) {
    uint32_t index = 0;
    Buffer buffer = newBufferWithMS(get_maximum_length(operations));

    while (operations[index].name[0] != 0) {
        BufferOperation operation = operations[index];

        fprintf(stderr, "rendering %s\n", operation.name);

        operation.render(operation, buffer);

        operation.delete(&operations[index]);
        index++;
    }
    return buffer;
}


int main(int argc, char *argv[]) {
    struct ProcessOptions options = parse_command_line(argc, argv);

    BufferOperation *operations = parse(options.command);

    if (operations) {
        Buffer buffer = render(operations);
        writeBufferToPath(buffer, options.output_filename);
        deleteBuffer(&buffer);
    } else {
        Buffer buffer = newBufferWithMS(1000);

        BufferOperation oscillator = newSinusOscillator();

        oscillator.render(oscillator, buffer);
        oscillator.delete(&oscillator);

        writeBufferToPath(buffer, options.output_filename);
        deleteBuffer(&buffer);
    }

    return 0;
}
