#include "stb_image.h"
#include "io/image_loader.h"
#include "core/image.h"

Image* image_load_from_file(const char* filename) {
    // Use STB to load raw pixel data
    int width, height, channels;
    unsigned char* stb_data = stbi_load(filename, &width, &height, &channels, 0);
    
    if (!stb_data) {
        fprintf(stderr, "Image load failed for '%s': %s\n", filename, stbi_failure_reason());
        return NULL;
    }

    // Determine image type from channel count
    ImageType type;
    switch(channels) {
        case 1: type = IMAGE_TYPE_GRAY; break;
        case 3: type = IMAGE_TYPE_RGB; break;
        case 4: type = IMAGE_TYPE_RGBA; break;
        default:
            stbi_image_free(stb_data);
            fprintf(stderr, "Unsupported channel count: %d in file '%s'\n", channels, filename);
            return NULL;
    }

    // Create image using core module
    Image* img = image_create(width, height, type);
    if (!img) {
        stbi_image_free(stb_data);
        return NULL;
    }

    // Copy STB data into our own buffer
    const size_t data_size = width * height * channels;
    memcpy(img->pixels, stb_data, data_size);
    
    // Free STB's original buffer
    stbi_image_free(stb_data);

    return img;
}