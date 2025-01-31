#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "core/image.h"
#include "preprocessing/grayscale.h"
#include "preprocessing/invert.h"
#include "io/image_loader.h"
#include "io/image_saver.h"
#include "core/ascii_ramp.h"
#include "conversion/intensity_map.h"

int main() {
    AsciiRamp ramp = {
        .characters = " .,:ilwW",
        .length = 8
    };
    char* filename = "../local/pikachu.png";
    Image* img = image_load_from_file(filename);
    
    if (img) {
        image_to_grayscale(img, 0);
        char* output = intensity_map(img, &ramp);
        if (output) {
            printf("%s\n", output);
            free(output);
        }
        

        image_free(img); // Single consistent free call
    }
    return 0;
}