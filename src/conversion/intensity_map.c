#include <stdio.h>
#include <stdlib.h>
#include "core/image.h"
#include "core/ascii_ramp.h"
#include "conversion/intensity_map.h"

char* intensity_map(const Image* img, const AsciiRamp* ramp){
    if (!image_validate(img)) {
        fprintf(stderr, "Invalid image\n");
        return NULL;
    }
    if (!ascii_ramp_validate(ramp)) {
        fprintf(stderr, "Invalid ASCII ramp\n");
        return NULL;
    }

    const int ramp_length = ramp->length;

    char* output = malloc(img->width * img->height + img->height);
    if (!output) {
        perror("Failed to allocate output buffer");
        return NULL;
    }

    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            const uint8_t* pixel = image_pixel_at(img, x, y);
            const uint8_t intensity = pixel[0];
            const int ramp_index = intensity * (ramp_length-1) / 255;
            *output++ = ramp->characters[ramp_index];
        }
        *output++ = '\n';
    }

    return output;

}