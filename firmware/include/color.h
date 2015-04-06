/*
 * Originally from lys
 * https://github.com/eBrnd/lys/blob/master/software/color.h
 */

#ifndef COLOR_H_5A430E2AC3
#define COLOR_H_5A430E2AC3

#include <stdint.h>

struct color_rgb {
	// Values from 0 .. 255.
	uint8_t r, g, b;
};

struct color_hsv {
	// h from 0 .. 1535; s and v 0 .. 255.
	uint16_t h;
	uint8_t s, v;
};

void color_hsv2rgb(struct color_hsv* in, struct color_rgb* out);

#endif
