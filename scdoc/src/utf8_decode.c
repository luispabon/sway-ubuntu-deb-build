#include <stdint.h>
#include <stddef.h>
#include "unicode.h"

uint8_t masks[] = {
	0x7F,
	0x1F,
	0x0F,
	0x07,
	0x03,
	0x01
};

uint32_t utf8_decode(const char **char_str) {
	uint8_t **s = (uint8_t **)char_str;

	uint32_t cp = 0;
	if (**s < 128) {
		// shortcut
		cp = **s;
		++*s;
		return cp;
	}
	int size = utf8_size((char *)*s);
	if (size == -1) {
		++*s;
		return UTF8_INVALID;
	}
	uint8_t mask = masks[size - 1];
	cp = **s & mask;
	++*s;
	while (--size) {
		cp <<= 6;
		cp |= **s & 0x3f;
		++*s;
	}
	return cp;
}
