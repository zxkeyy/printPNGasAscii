#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "core/config.h"

struct option long_options[] = {
    {"input", required_argument, NULL, 'i'},
    {"output", required_argument, NULL, 'o'},
    {"no-terminal-output", no_argument, NULL, 'n'},
    {"ascii-gradient", required_argument, NULL, 'g'},   
    {"width", required_argument, NULL, 'w'},
    {"height", required_argument, NULL, 'h'},
    {"alpha", required_argument, NULL, 'a'},
    {"invert", no_argument, NULL, 'r'},
    {"verbose", no_argument, NULL, 'v'},
    {"help", no_argument, NULL, '?'},
    {NULL, 0, NULL, 0}
};

void print_usage(const char* program_name) {
    printf("Usage: %s [options]\n"
           "Options:\n"
           "  -i, --input    <input>     Input file (JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC image)\n"
           "  -o, --output   <output>    Output file (optional)\n"
           "  -n, --no-terminal-output   Disable terminal output\n"
           "  -g --ascii-gradient <gradient> ASCII gradient to use (default: ' .:-=+*#@&8B$@')\n"
           "  -w, --width    <width>     Output width in characters ('-1' to keep the width of the source image, default: 150 character)\n"
           "  -h, --height   <height>    Output height in characters ('-1' to keep the height of the source image, default: 75 character)\n"
           "  -a, --alpha    <alpha>     Defines brightness of background for images with alpha transparency (0 - 255, default=0)\n"
           "  -r, --invert               Invert colors\n"
           "  -v, --verbose              Verbose output\n"
           "  -?, --help                 Display this help message\n",
           program_name);
}

int parse_arguments(int argc, char* argv[], AppConfig* config){
    int opt;
    while ((opt = getopt_long(argc, argv, "i:o:w:h:g:a:nrv?", long_options, NULL)) != -1) {
        switch (opt) {
            case 'i': config->input_path = optarg; break;
            case 'o': config->output_path = optarg; break;
            case 'n': config->no_terminal_output = 1; break;
            case 'g': config->ramp.characters = optarg; config->ramp.length = strlen(optarg); break;
            case 'w': config->width = atoi(optarg); break;
            case 'h': config->height = atoi(optarg); break;
            case 'a': config->alpha = atoi(optarg); break;
            case 'r': config->inverse_colors = 1; break;
            case 'v': config->verbose = 1; break;
            case '?': print_usage(argv[0]); return 1;
            default:
                return -1;
        }
    }

    return 0;
}

int validate_config(AppConfig* config) {
    if (!config->input_path) {
        fprintf(stderr, "Input path is required\n");
        return -1;
    }

    if ((config->width <= 0 && config->width != -1) || (config->height <= 0  && config->height != -1)) {
        fprintf(stderr, "Invalid output dimensions: %dx%d\n", config->width, config->height);
        return -1;
    }

    if (config->alpha < 0 || config->alpha > 255) {
        fprintf(stderr, "Alpha value must be between 0 and 255\n");
        return -1;
    }

    return 0;
}