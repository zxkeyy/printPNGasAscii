#include <stdbool.h>
#include <core/ascii_ramp.h>

bool ascii_ramp_validate(const AsciiRamp* ramp) {
    return ramp && ramp->characters && ramp->length > 0;
}