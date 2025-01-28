#include <stdio.h>
#include <stdlib.h>
#include <core/image.h>
#include <preprocessing/grayscale.h>

uint8_t RGB_blend(uint8_t r, uint8_t g, uint8_t b) {
    return (uint8_t)(0.3f * (float)r + 0.6f * (float)g + 0.1f * (float)b);
}

uint8_t RGBA_blend(uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint8_t alpha_value) {
    const uint8_t rgb = RGB_blend(r, g, b);
    return (1 - a / 255.0) * alpha_value + (a / 255.0) * rgb;
}

void RGB_image_to_grayscale(Image* img) {
    if(img->type != IMAGE_TYPE_RGB) {
        fprintf(stderr, "Image is not RGB\n");
        return;
    }

    uint8_t* pixels = malloc(img->width * img->height * sizeof(uint8_t));
    if(!pixels) {
        perror("Failed to allocate grayscale buffer");
        return;
    }

    for(int y = 0; y < img->height; y++) {
        for(int x = 0; x < img->width; x++) {
            const uint8_t* pixel = image_pixel_at(img, x, y);
            pixels[y * img->width + x] = RGB_blend(pixel[0], pixel[1], pixel[2]);
        }
    }

    free(img->pixels);
    img->pixels = pixels;
    img->type = IMAGE_TYPE_GRAY;
    img->channels = 1;
}

void RGBA_image_to_grayscale(Image* img, uint8_t alpha_value) {
    if(img->type != IMAGE_TYPE_RGBA) {
        fprintf(stderr, "Image is not RGBA\n");
        return;
    }

    uint8_t* pixels = malloc(img->width * img->height * sizeof(uint8_t));
    if(!pixels) {
        perror("Failed to allocate grayscale buffer");
        return;
    }

    for(int y = 0; y < img->height; y++) {
        for(int x = 0; x < img->width; x++) {
            const uint8_t* pixel = image_pixel_at(img, x, y);
            pixels[y * img->width + x] = RGBA_blend(pixel[0], pixel[1], pixel[2], pixel[3], alpha_value);
        }
    }

    free(img->pixels);
    img->pixels = pixels;
    img->type = IMAGE_TYPE_GRAY;
    img->channels = 1;
}