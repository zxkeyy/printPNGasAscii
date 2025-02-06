#include <stdio.h>

#include "core/image.h"
#include "preprocessing/dither.h"

#define CLAMP(x) (x < 0 ? 0 : (x > 255 ? 255 : x))

void floyd_steinberg_dither(Image* img, uint8_t threshold) {
    if (img->type != IMAGE_TYPE_GRAY) {
        fprintf(stderr, "Image is not grayscale\n");
        return;
    }

    const int width = img->width;
    const int height = img->height;
    const int channels = img->channels;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint8_t* pixel = image_pixel_at(img, x, y);
            const uint8_t old_pixel = pixel[0];
            const uint8_t new_pixel = old_pixel < 128 ? 0 : 255;
            const int error = old_pixel - new_pixel;
            pixel[0] = new_pixel;

            if (x + 1 < width) {
                pixel = image_pixel_at(img, x + 1, y);
                pixel[0] = CLAMP(pixel[0] + error * 7 / 16);
            }

            if (y + 1 < height) {
                pixel = image_pixel_at(img, x, y + 1);
                pixel[0] = CLAMP(pixel[0] + error * 5 / 16);
            }

            if (x - 1 >= 0 && y + 1 < height) {
                pixel = image_pixel_at(img, x - 1, y + 1);
                pixel[0] = CLAMP(pixel[0] + error * 3 / 16);
            }

            if (x + 1 < width && y + 1 < height) {
                pixel = image_pixel_at(img, x + 1, y + 1);
                pixel[0] = CLAMP(pixel[0] + error * 1 / 16);
            }
        }
    }
}