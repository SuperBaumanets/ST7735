#ifndef FONT_H_
#define FONT_H_

#include <stdint.h>

typedef struct {
    uint8_t width;
    uint8_t height;
    const unsigned char *data;
}font_t;

extern font_t font8;

#endif // #ifndef FONT_H_