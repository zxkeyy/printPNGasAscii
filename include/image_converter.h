// image_converter.h
#ifndef IMAGE_CONVERTER_H
#define IMAGE_CONVERTER_H

#include "config.h"

// Image conversion modes
typedef enum {
    CONVERSION_GRAYSCALE,
    CONVERSION_BINARY,
    CONVERSION_DETAILED
} ImageConversionMode;

// ASCII character mapping structure
typedef struct {
    char *chars;         // String of characters for mapping
    int char_count;      // Number of characters in mapping
} AsciiCharMap;

// Function to convert an image to ASCII art
int convert_image_to_ascii(AppConfig *config);

// Function to create an ASCII character map
AsciiCharMap* create_ascii_char_map(ImageConversionMode mode);

// Function to free the ASCII character map
void free_ascii_char_map(AsciiCharMap *map);

// Advanced image processing options
typedef struct {
    double brightness_factor;  // Adjust image brightness
    double contrast_factor;    // Adjust image contrast
    int smoothing_level;       // Image smoothing intensity
} ImageProcessingOptions;

// Additional utility functions for image processing
int adjust_image_brightness(unsigned char *image, int width, int height, int channels, double factor);
int apply_image_contrast(unsigned char *image, int width, int height, int channels, double factor);

#endif // IMAGE_CONVERTER_H