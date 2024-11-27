#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

#include "config.h"

AsciiImage* convert_image_to_ascii(
    const unsigned char* image_data,
    int image_width,
    int image_height,
    int channels,
    const ImageConversionConfig* config
){
    //load the image
    unsigned char *imageData = stbi_load(argv[0], &width, &height, &channels, 0);
}