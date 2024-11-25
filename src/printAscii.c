// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "image_converter.h"
#include "video_converter.h"
#include "video_player.h"
#include "utils.h"

// Centralized error handling
void handle_error(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}

// Print detailed usage instructions
void print_usage(const char *program_name) {
    printf("ASCII Media Converter\n");
    printf("Usage: %s [options]\n", program_name);
    printf("Options:\n");
    printf("  -i <input>     Input file path (required)\n");
    printf("  -o <output>    Output file path (optional)\n");
    printf("  -m <mode>      Operation mode:\n");
    printf("                 0 - Image to ASCII\n");
    printf("                 1 - Video to ASCII\n");
    printf("                 2 - Play ASCII Video\n");
    printf("                 3 - Create ASCII Dictionary\n");
    printf("  -w <width>     Output width (default: 80)\n");
    printf("  -f <fps>       Frame rate for video (default: 10)\n");
    printf("  -a <alpha>     Alpha value threshold (default: 128)\n");
    printf("  -t <threshold> Pixel intensity threshold (default: 128)\n");
    printf("  -r             Invert colors\n");
    printf("  -v             Verbose mode\n");
}

int main(int argc, char *argv[]) {
    // Initialize configuration with default values
    AppConfig config = {
        .mode = MODE_IMAGE_TO_ASCII,
        .input_path = NULL,
        .output_path = NULL,
        .width = 80,           // Default terminal width
        .frame_rate = 10,      // Default frame rate
        .conversion_mode = 1,  // Default conversion mode
        .alpha = 128,          // Default alpha threshold
        .threshold = 128,      // Default pixel threshold
        .inverse_colors = 0,   // Default: no color inversion
        .verbose = 0           // Default: quiet mode
    };

    // Parse command-line arguments
    int parse_result = parse_arguments(argc, argv, &config);
    if (parse_result != 0) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    // Validate input path
    if (config.input_path == NULL) {
        handle_error("No input file specified");
    }

    // Verbose logging if enabled
    if (config.verbose) {
        printf("Input: %s\n", config.input_path);
        printf("Output: %s\n", config.output_path ? config.output_path : "Not specified");
        printf("Mode: %d\n", config.mode);
    }

    // Dispatch to appropriate handler based on mode
    switch (config.mode) {
        case MODE_IMAGE_TO_ASCII:
            return convert_image_to_ascii(&config);
        
        case MODE_VIDEO_TO_ASCII:
            return convert_video_to_ascii(&config);
        
        case MODE_PLAY_ASCII:
            return play_ascii_video(&config);
        
        case MODE_CREATE_DICTIONARY:
            return create_ascii_dictionary(&config);
        
        default:
            handle_error("Invalid operation mode");
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}