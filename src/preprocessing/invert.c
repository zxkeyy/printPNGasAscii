#include <stdio.h>
#include <stdlib.h>
#include <core/image.h>
#include <preprocessing/invert.h>

void invert_grayscale_image(Image* img) {
    if(img->type != IMAGE_TYPE_GRAY) {
        fprintf(stderr, "Image is not grayscale\n");
        return;
    }

    for(int y = 0; y < img->height; y++) {
        for(int x = 0; x < img->width; x++) {
            uint8_t* pixel = image_pixel_at(img, x, y);
            *pixel = 255 - *pixel;
        }
    }
}

void invert_rgb_image(Image* img) {
    if(img->type != IMAGE_TYPE_RGB) {
        fprintf(stderr, "Image is not RGB\n");
        return;
    }

    for(int y = 0; y < img->height; y++) {
        for(int x = 0; x < img->width; x++) {
            uint8_t* pixel = image_pixel_at(img, x, y);
            pixel[0] = 255 - pixel[0];
            pixel[1] = 255 - pixel[1];
            pixel[2] = 255 - pixel[2];
        }
    }
}

void invert_rgba_image(Image* img) {
    if(img->type != IMAGE_TYPE_RGBA) {
        fprintf(stderr, "Image is not RGBA\n");
        return;
    }

    for(int y = 0; y < img->height; y++) {
        for(int x = 0; x < img->width; x++) {
            uint8_t* pixel = image_pixel_at(img, x, y);
            pixel[0] = 255 - pixel[0];
            pixel[1] = 255 - pixel[1];
            pixel[2] = 255 - pixel[2];
        }
    }
}