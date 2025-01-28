#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "../core/image.h"

void RGB_image_to_grayscale(const Image* img);
void RGBA_image_to_grayscale(const Image* img, int alpha_value);

#endif // GRAYSCALE_H