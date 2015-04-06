/*
 * Originally from lys
 * https://github.com/eBrnd/lys/blob/master/software/color.h
 */

#include "color.h"

// Logarithm table for smoother brightness changes.
const uint16_t pwmtable[]  = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7,
	7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 12, 12, 12,
	13, 13, 13, 14, 14, 15, 15, 16, 16, 16, 17, 17, 18, 18, 19, 19, 20, 21, 21,
	22, 22, 23, 24, 24, 25, 26, 26, 27, 28, 29, 30, 30, 31, 32, 33, 34, 35, 36,
	37, 38, 39, 40, 41, 42, 43, 45, 46, 47, 48, 50, 51, 53, 54, 56, 57, 59, 60,
	62, 64, 65, 67, 69, 71, 73, 75, 77, 79, 81, 84, 86, 88, 91, 93, 96, 98, 101,
	104, 107, 110, 113, 116, 119, 122, 126, 129, 133, 136, 140, 144, 148, 152,
	156, 161, 165, 170, 174, 179, 184, 189, 194, 199, 205, 210, 216, 222, 228,
	235, 241, 248, 255
};

// HSV to RGB color space conversion.
// We use a HSV range from 0 .. 1535 so every (3*8bit) RGB value can be expressed as a HSV value.
void color_hsv2rgb(struct color_hsv* in, struct color_rgb* out) {

	uint16_t v = pwmtable[in->v];

	uint16_t col = ((uint16_t)v * in->s) / 255UL; // Span between darkest and brightest channel.
	uint16_t min = v - col; // Minimum (brightness of the darkest channel).
	uint8_t ramp = in->h >> 8; // Ramp of the HSV diagram we're on.
	uint16_t hue = in->h % 256; // Position on hue ramp.

	if (ramp % 2) // We're on a downward ramp.
		hue = 255 - hue;

	hue = ((uint16_t)hue * col) / 255UL; // Scale position on ramp to slope.
	hue += min;

	switch (ramp) {
	case 0:  // Green up.
		out->r = v;
		out->g = hue;
		out->b = min;
		break;
	case 1:  // Red down.
		out->r = hue;
		out->g = v;
		out->b = min;
		break;
	case 2:  // Blue up.
		out->r = min;
		out->g = v;
		out->b = hue;
		break;
	case 3:  // Green down.
		out->r = min;
		out->g = hue;
		out->b = v;
		break;
	case 4:  // Red up.
		out->r = hue;
		out->g = min;
		out->b = v;
		break;
	case 5:  // Blue down.
		out->r = v;
		out->g = min;
		out->b = hue;
		break;
	}
}
