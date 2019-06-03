#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "unicode.h"
#include "util.h"

void parser_fatal(struct parser *parser, const char *err) {
	fprintf(stderr, "Error at %d:%d: %s\n",
			parser->line, parser->col, err);
	fclose(parser->input);
	fclose(parser->output);
	exit(1);
}

uint32_t parser_getch(struct parser *parser) {
	if (parser->qhead) {
		return parser->queue[--parser->qhead];
	}
	if (parser->str) {
		uint32_t ch = utf8_decode(&parser->str);
		if (!ch || ch == UTF8_INVALID) {
			parser->str = NULL;
			return UTF8_INVALID;
		}
		return ch;
	}
	uint32_t ch = utf8_fgetch(parser->input);
	if (ch == '\n') {
		parser->col = 0;
		++parser->line;
	} else {
		++parser->col;
	}
	return ch;
}

void parser_pushch(struct parser *parser, uint32_t ch) {
	if (ch != UTF8_INVALID) {
		parser->queue[parser->qhead++] = ch;
	}
}

void parser_pushstr(struct parser *parser, const char *str) {
	parser->str = str;
}

int roff_macro(struct parser *p, char *cmd, ...) {
	FILE *f = p->output;
	int l = fprintf(f, ".%s", cmd);
	va_list ap;
	va_start(ap, cmd);
	const char *arg;
	while ((arg = va_arg(ap, const char *))) {
		fputc(' ', f);
		fputc('"', f);
		while (*arg) {
			uint32_t ch = utf8_decode(&arg);
			if (ch == '"') {
				fputc('\\', f);
				++l;
			}
			l += utf8_fputch(f, ch);
		}
		fputc('"', f);
		l += 3;
	}
	va_end(ap);
	fputc('\n', f);
	return l + 1;
}
