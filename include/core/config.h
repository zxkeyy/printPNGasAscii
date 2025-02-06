#ifndef CONFIG_H
#define CONFIG_H

#include "core/ascii_ramp.h"

typedef struct {
    char* input_path;
    char* output_path;
    int no_terminal_output;
    int width;
    int height;
    int alpha;
    int inverse_colors;
    int dither;
    int threshold;
    int verbose;
    AsciiRamp ramp;
} AppConfig;

void print_usage(const char* program_name);
int parse_arguments(int argc, char* argv[], AppConfig* config);
int validate_config(AppConfig* config);

#endif // CONFIG_H