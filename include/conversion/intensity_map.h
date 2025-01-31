#ifndef INTENSITY_MAP_H
#define INTENSITY_MAP_H

#include "core/image.h"
#include "core/ascii_ramp.h"

char* intensity_map(const Image* img, const AsciiRamp* ramp);

#endif // INTENSITY_MAP_H