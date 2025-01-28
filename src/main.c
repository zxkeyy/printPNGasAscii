#include <stdio.h>
#include <stdint.h>

#include "core/image.h"
#include "io/image_loader.h"

int main() {
    char* filename = "../local/pikachu.png";
    Image* img = image_load_from_file(filename);
    
    if (img) {
        printf("Loaded image: %dx%d, channels: %d\n", img->width, img->height, img->channels);
        printf("First pixel: %d, %d, %d, %d\n", img->pixels[0], img->pixels[1],img->pixels[2],img->pixels[3]);
        image_free(img); // Single consistent free call
    }
    return 0;
}