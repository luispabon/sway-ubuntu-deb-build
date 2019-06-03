#ifndef _SCDOC_STRING_H
#define _SCDOC_STRING_H
#include <stdint.h>

struct str {
	char *str;
	size_t len, size;
};

typedef struct str str_t;

str_t *str_create();
void str_free(str_t *str);
void str_reset(str_t *str);
int str_append_ch(str_t *str, uint32_t ch);

#endif
