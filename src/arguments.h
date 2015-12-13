
struct ProcessOptions {
    int  verbose;
    char *output_filename;
    char *command;
};

struct ProcessOptions parse_command_line(int argc, char *argv[]);
