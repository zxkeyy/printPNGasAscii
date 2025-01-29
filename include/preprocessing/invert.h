#ifndef INVERT_H
#define INVERT_H

#include "../core/image.h"

void invert_grayscale_image(Image* img);
void invert_rgb_image(Image* img);
void invert_rgba_image(Image* img);

#endif // INVERT_H