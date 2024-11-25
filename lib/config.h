// config.h
#ifndef CONFIG_H
#define CONFIG_H

// Modes of operation
typedef enum {
    MODE_IMAGE_TO_ASCII = 0,
    MODE_VIDEO_TO_ASCII = 1,
    MODE_PLAY_ASCII = 2,
    MODE_CREATE_DICTIONARY = 3
} OperationMode;

// Configuration struct
typedef struct {
    OperationMode mode;
    char *input_path;
    char *output_path;
    int width;           // Desired output width
    int frame_rate;      // For video conversion
    int conversion_mode; // Conversion algorithm mode
    int alpha;           // Alpha threshold
    int threshold;       // Pixel intensity threshold
    int inverse_colors;  // Invert colors flag
    int verbose;         // Verbose output flag
} AppConfig;

// Argument parsing function declaration
int parse_arguments(int argc, char *argv[], AppConfig *config);

#endif // CONFIG_H