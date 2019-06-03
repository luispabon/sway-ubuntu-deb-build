#include <stdint.h>
#include <stdio.h>
#include "unicode.h"

size_t utf8_fputch(FILE *f, uint32_t ch) {
	char buffer[UTF8_MAX_SIZE];
	char *ptr = buffer;
	size_t size = utf8_encode(ptr, ch);
	return fwrite(&buffer, 1, size, f);
}
