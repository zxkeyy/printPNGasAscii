#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "io/image_saver.h"


bool image_save_to_file(const Image* img, const char* filename) {
    // Determine STB image type from our image type
    int stb_type;
    switch (img->type) {
        case IMAGE_TYPE_GRAY: stb_type = STBI_grey; break;
        case IMAGE_TYPE_RGB: stb_type = STBI_rgb; break;
        case IMAGE_TYPE_RGBA: stb_type = STBI_rgb_alpha; break;
        default:
            fprintf(stderr, "Unsupported image type\n");
            return false;
    }

    // Write image to file using STB
    int success = stbi_write_png(filename, img->width, img->height, img->channels, img->pixels, img->width * img->channels);
    if (!success) {
        fprintf(stderr, "Failed to write image to file: %s\n", filename);
        return false;
    }

    return true;
}