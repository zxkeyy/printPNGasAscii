#ifndef IMAGE_CONVERTER_H
#define IMAGE_CONVERTER_H

#include "config.h"
#include <stddef.h>

// Chunk division strategies
typedef enum {
    CHUNK_PIXEL,          // Single pixel per chunk
    CHUNK_FIXED_SIZE,     // Fixed-size rectangular chunks
    CHUNK_ADAPTIVE,       // Adaptive chunk sizing based on image content
    CHUNK_TERMINAL_ASPECT // Chunks matching terminal character aspect
} ChunkingStrategy;

// Preprocessing techniques
typedef enum {
    PREPROCESS_NONE,
    PREPROCESS_BLUR,
    PREPROCESS_SHARPEN,
    PREPROCESS_NORMALIZE,
    PREPROCESS_EQUALIZE_HISTOGRAM
} PreprocessingMethod;

// Chunk conversion method signature
typedef char (*ChunkConversionFunc)(
    const unsigned char* chunk_data, 
    int chunk_width, 
    int chunk_height, 
    int channels
);

// Image chunk structure
typedef struct {
    unsigned char* data;   // Raw pixel data for the chunk
    int width;             // Chunk width
    int height;            // Chunk height
    int channels;          // Number of color channels
    double average_brightness;
} ImageChunk;

// Image conversion configuration
typedef struct {
    // Chunking parameters
    ChunkingStrategy chunking_strategy;
    int chunk_width;       // For fixed-size chunks
    int chunk_height;      // For fixed-size chunks
    
    // Preprocessing
    PreprocessingMethod preprocessing;
    
    // Conversion method
    ChunkConversionFunc conversion_method;
    
    // Additional options
    int invert_brightness;
    double brightness_threshold;
    
    // Custom character set (optional)
    const char* custom_charset;
} ImageConversionConfig;

// Chunk division functions
ImageChunk* divide_image_into_chunks(
    const unsigned char* image_data,
    int image_width,
    int image_height,
    int channels,
    const ImageConversionConfig* config,
    int* chunk_count
);

// Free chunk array
void free_image_chunks(ImageChunk* chunks, int chunk_count);

// ASCII conversion result
typedef struct {
    char** ascii_art;
    int width;
    int height;
} AsciiImage;

// Main conversion function
AsciiImage* convert_image_to_ascii(
    const unsigned char* image_data,
    int image_width,
    int image_height,
    int channels,
    const ImageConversionConfig* config
);

// Default conversion methods
char chunk_to_ascii_brightness(
    const unsigned char* chunk_data, 
    int chunk_width, 
    int chunk_height, 
    int channels
);

char chunk_to_ascii_detail(
    const unsigned char* chunk_data, 
    int chunk_width, 
    int chunk_height, 
    int channels
);

// Utility functions
double calculate_chunk_brightness(
    const unsigned char* chunk_data, 
    int chunk_width, 
    int chunk_height, 
    int channels
);

// Preprocessing functions
unsigned char* preprocess_image(
    unsigned char* image_data,
    int width,
    int height,
    int channels,
    PreprocessingMethod method
);

// Free functions
void free_ascii_image(AsciiImage* ascii_image);

#endif // IMAGE_CONVERTER_H