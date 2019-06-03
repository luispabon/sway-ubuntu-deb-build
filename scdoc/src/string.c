#include <stdlib.h>
#include <stdint.h>
#include "str.h"
#include "unicode.h"

static int ensure_capacity(str_t *str, size_t len) {
	if (len + 1 >= str->size) {
		char *new = realloc(str->str, str->size * 2);
		if (!new) {
			return 0;
		}
		str->str = new;
		str->size *= 2;
	}
	return 1;
}

str_t *str_create() {
	str_t *str = calloc(sizeof(str_t), 1);
	str->str = malloc(16);
	str->size = 16;
	str->len = 0;
	str->str[0] = '\0';
	return str;
}

void str_free(str_t *str) {
	if (!str) return;
	free(str->str);
	free(str);
}

int str_append_ch(str_t *str, uint32_t ch) {
	int size = utf8_chsize(ch);
	if (size <= 0) {
		return -1;
	}
	if (!ensure_capacity(str, str->len + size)) {
		return -1;
	}
	utf8_encode(&str->str[str->len], ch);
	str->len += size;
	str->str[str->len] = '\0';
	return size;
}
