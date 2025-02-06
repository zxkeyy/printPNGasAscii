#ifndef DITHER_H
#define DITHER_H

#include "core/image.h"

void floyd_steinberg_dither(Image* img, uint8_t threshold);

#endif // DITHER_H