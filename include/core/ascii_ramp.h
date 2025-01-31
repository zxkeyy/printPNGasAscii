#ifndef ASCII_RAMP_H
#define ASCII_RAMP_H

typedef struct {
    const char* characters;
    int length;
} AsciiRamp;

bool ascii_ramp_validate(const AsciiRamp* ramp);

#endif // ASCII_RAMP_H