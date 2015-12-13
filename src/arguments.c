#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "arguments.h"

void print_usage() {
    printf("usage: asciisfx [--output filename.wav] command\n");
    exit(-1);
}

struct ProcessOptions parse_command_line(int argc, char *argv[]) {
    struct ProcessOptions options = {0, 0, ""};

    struct option long_options[] = {
        {"verbose", no_argument, &options.verbose, 1},
        {"output",  required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };

    int c;

    while (1) {
        int option_index = 0;

        c = getopt_long(argc, argv, "o:",
                        long_options, &option_index);

        switch (c) {
            case -1:
                if (optind == argc - 1) {
                    options.command = argv[optind];
                    return options;
                }
                print_usage();

            case 0:
                break;

            case 'o':
                options.output_filename = optarg;
                break;

            default:
                print_usage();
        }
    }
}
