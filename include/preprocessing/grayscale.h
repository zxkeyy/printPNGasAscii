#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "../core/image.h"

void RGB_image_to_grayscale(Image* img);
void RGBA_image_to_grayscale(Image* img, uint8_t alpha_value);

#endif // GRAYSCALE_H