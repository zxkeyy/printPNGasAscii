#include <stdio.h>
#include <stdint.h>

#include "core/image.h"
#include "preprocessing/grayscale.h"
#include "preprocessing/invert.h"
#include "io/image_loader.h"
#include "io/image_saver.h"

int main() {
    char* filename = "../local/pikachu2.png";
    Image* img = image_load_from_file(filename);
    
    if (img) {
        RGB_image_to_grayscale(img);
        invert_grayscale_image(img);

        image_save_to_png_file(img, "pikachu_gray.png");

        image_free(img); // Single consistent free call
    }
    return 0;
}