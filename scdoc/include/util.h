#ifndef _SCDOC_PARSER_H
#define _SCDOC_PARSER_H
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

struct parser {
	FILE *input, *output;
	int line, col;
	int qhead;
	uint32_t queue[32];
	uint32_t flags;
	const char *str;
	int fmt_line, fmt_col;
};

enum formatting {
	FORMAT_BOLD = 1,
	FORMAT_UNDERLINE = 2,
	FORMAT_LAST = 4,
};

void parser_fatal(struct parser *parser, const char *err);
uint32_t parser_getch(struct parser *parser);
void parser_pushch(struct parser *parser, uint32_t ch);
void parser_pushstr(struct parser *parser, const char *str);
int roff_macro(struct parser *p, char *cmd, ...);

#endif
