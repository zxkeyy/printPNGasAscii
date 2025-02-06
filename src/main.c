#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "core/image.h"
#include "core/config.h"
#include "preprocessing/dither.h"
#include "preprocessing/grayscale.h"
#include "preprocessing/invert.h"
#include "preprocessing/resize.h"
#include "io/image_loader.h"
#include "io/image_saver.h"
#include "core/ascii_ramp.h"
#include "conversion/intensity_map.h"

const AsciiRamp DEFAULT_RAMP = {
    .characters = " .:-=+*#@&8B$@",
    .length = 14
};

const AppConfig DEFAULT_CONFIG = {
    .input_path = NULL,
    .output_path = NULL,
    .no_terminal_output = 0,
    .width = 150,
    .height = 0,
    .alpha = 0,
    .inverse_colors = 0,
    .dither = 0,
    .threshold = 128,
    .font_aspect_ratio = 0.45,
    .verbose = 0,
    .ramp = {0}
};

int main(int argc, char *argv[]) {
    AppConfig config = DEFAULT_CONFIG;
    config.ramp = DEFAULT_RAMP;

    if (parse_arguments(argc, argv, &config) != 0) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    if (validate_config(&config) != 0) {
        return EXIT_FAILURE;
    }

    Image* img = image_load_from_file(config.input_path);
    if (!img) {
        fprintf(stderr, "Failed to load image\n");
        return EXIT_FAILURE;
    }
    //debug
    image_save_to_png_file(img, "1original.png");

    if (config.width == -1){
        config.width = img->width;
    }
    if (config.height == -1){
        config.height = (int)(float)img->height * config.font_aspect_ratio;
    }

    // calculate width or height if one of them is 0 to keep aspect ratio
    if (config.width == 0){
        config.width = (int)(((float)config.height / img->height * img->width) / config.font_aspect_ratio);
    }
    if (config.height == 0){
        config.height = (int)(((float)config.width / img->width * img->height) * config.font_aspect_ratio);
    }

    image_resize(img, config.width, config.height);
    //debug
    image_save_to_png_file(img, "2resized.png");

    if (config.inverse_colors) {
        invert_image(img);
        //debug
        image_save_to_png_file(img, "3inverted.png");
    }

    image_to_grayscale(img, config.alpha);
    //debug
    image_save_to_png_file(img, "4gray.png");

    if (config.dither) {
        floyd_steinberg_dither(img, config.threshold);
        //debug
        image_save_to_png_file(img, "5dithered.png");
    }

    char* output = intensity_map(img, &config.ramp);
    if (!output) {
        fprintf(stderr, "Failed to generate intensity map\n");
        image_free(img);
        return EXIT_FAILURE;
    }

    if (!config.no_terminal_output) {
        printf("%s\n", output);
    }

    if (config.output_path) {
        FILE* file = fopen(config.output_path, "w");
        if (!file) {
            perror("Failed to open output file");
            free(output);
            image_free(img);
            return EXIT_FAILURE;
        }

        fprintf(file, "%s", output);
        fclose(file);
    }

    free(output);
    image_free(img);
    return EXIT_SUCCESS;
}
