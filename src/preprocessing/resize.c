#include <stdio.h>
#include <stdlib.h>
#include "stb_image_resize2.h"
#include "core/image.h"
#include "preprocessing/resize.h"

void image_resize(Image* img, int new_width, int new_height){
    if (img->width == new_width && img->height == new_height) return;
    if (new_width <= 0 || new_height <= 0) {
        fprintf(stderr, "Invalid image dimensions: %dx%d\n", new_width, new_height);
        return;
    }

    if (!image_validate(img)) { 
        fprintf(stderr, "Invalid image\n"); 
        return; 
    }

    Image* resized = image_create(new_width, new_height, img->type);
    if (!resized) {
        fprintf(stderr, "Failed to allocate memory for resized image\n");
        return;
    }

    stbir_resize_uint8_srgb(img->pixels, img->width, img->height, 0, resized->pixels, new_width, new_height, 0, img->channels);

    free(img->pixels);
    img->pixels = resized->pixels;
    img->width = new_width;
    img->height = new_height;
    resized->pixels = NULL;
    image_free(resized);
}