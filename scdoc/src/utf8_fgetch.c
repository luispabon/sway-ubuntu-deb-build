#include <stdint.h>
#include <stdio.h>
#include "unicode.h"

uint32_t utf8_fgetch(FILE *f) {
	char buffer[UTF8_MAX_SIZE];
	int c = fgetc(f);
	if (c == EOF) {
		return UTF8_INVALID;
	}
	buffer[0] = (char)c;
	int size = utf8_size(buffer);

	if (size > UTF8_MAX_SIZE) {
		fseek(f, size - 1, SEEK_CUR);
		return UTF8_INVALID;
	}

	if (size > 1) {
		int amt = fread(&buffer[1], 1, size - 1, f);
		if (amt != size - 1) {
			return UTF8_INVALID;
		}
	}
	const char *ptr = buffer;
	return utf8_decode(&ptr);
}
