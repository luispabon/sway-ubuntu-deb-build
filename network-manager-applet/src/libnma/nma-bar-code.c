/* nma-bar-code.h - Renderer of a "QR" code
 *
 * Lubomir Rintel <lkundrak@v3.sk>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License as
 * published by the ree Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * Copyright 2018, 2019 Red Hat, Inc.
 */

#include "nm-default.h"

#include <stdint.h>

#include "nma-bar-code.h"

/*
 * The aim of this class is to provide a GObject-y QR code generator based
 * on qrcodegen library [1].  We purposefully include it directly instead
 * of compiling it separately, while providing a much less flexible (and
 * more straightforward) API. This way we the compiler does a good job at
 * slimming things down (chopping off half of the library) while allowing
 * us to leave the original source unmodified for easier maintenance.
 *
 * [1] https://github.com/nayuki/QR-Code-generator
 */

#pragma GCC visibility push(hidden)
NM_PRAGMA_WARNING_DISABLE("-Wdeclaration-after-statement")
#define NDEBUG
#include "qrcodegen.c"
NM_PRAGMA_WARNING_REENABLE
#pragma GCC visibility pop

struct _NMABarCode {
	GObject parent;
};

struct _NMABarCodeClass {
	GObjectClass parent_class;
};

typedef struct {
	uint8_t qrcode[qrcodegen_BUFFER_LEN_FOR_VERSION (qrcodegen_VERSION_MAX)];
} NMABarCodePrivate;

/**
 * SECTION:nma-bar-code
 * @title: NMABarCode
 *
 * A Bar Code object provides the means of drawing a QR code onto a cairo
 * context. Useful for rendering Wi-Fi network credential in a form that
 * can be optically scanned with a phone camera.
 */

G_DEFINE_TYPE_WITH_CODE (NMABarCode, nma_bar_code, G_TYPE_OBJECT,
                         G_ADD_PRIVATE (NMABarCode))

enum {
	PROP_0,
	PROP_TEXT,
	PROP_SIZE,

	LAST_PROP
};

#define NMA_BAR_CODE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), NMA_TYPE_BAR_CODE, NMABarCodePrivate))

/**
 * nma_bar_code_set_text:
 * @self: bar code instance
 * @text: new bar code text
 *
 * Regenerates the QR code for a different text.
 *
 * Since: 1.8.22
 */

void
nma_bar_code_set_text (NMABarCode *self, const char *text)
{
	g_object_set (self, NMA_BAR_CODE_TEXT, text, NULL);
}

/**
 * nma_bar_code_get_size:
 * @self: bar code instance
 *
 * Returns: the side of a QR code square.
 *
 * Since: 1.8.22
 */

int
nma_bar_code_get_size (NMABarCode *self)
{
	int size;

	g_object_get (self, NMA_BAR_CODE_SIZE, &size, NULL);
	return size;
}

/**
 * nma_bar_code_draw:
 * @self: bar code instance
 * @cr: cairo context
 *
 * Draws the QR code onto the given context.
 *
 * Since: 1.8.22
 */

void
nma_bar_code_draw (NMABarCode *self, cairo_t *cr)
{
	NMABarCodePrivate *priv = NMA_BAR_CODE_GET_PRIVATE (self);
	int x, y, size;

	size = qrcodegen_getSize (priv->qrcode);
	cairo_set_antialias (cr, CAIRO_ANTIALIAS_NONE);

	for (y = 0; y < size; y++) {
		for (x = 0; x < size; x++) {
			if (qrcodegen_getModule (priv->qrcode, x, y)) {
				cairo_rectangle (cr, x, y, 1, 1);
				cairo_fill (cr);
			}
		}
	}
}

static void
get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	NMABarCodePrivate *priv = NMA_BAR_CODE_GET_PRIVATE (object);

	switch (prop_id) {
	case PROP_SIZE:
		g_value_set_int (value, qrcodegen_getSize (priv->qrcode));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	NMABarCodePrivate *priv = NMA_BAR_CODE_GET_PRIVATE (object);
	uint8_t tempBuffer[qrcodegen_BUFFER_LEN_FOR_VERSION (qrcodegen_VERSION_MAX)];
	const char *text;
	bool success = FALSE;

	switch (prop_id) {
	case PROP_TEXT:
		text = g_value_get_string (value);
		if (text) {
			success = qrcodegen_encodeText(g_value_get_string (value),
			                               tempBuffer,
			                               priv->qrcode,
			                               qrcodegen_Ecc_LOW,
			                               qrcodegen_VERSION_MIN,
			                               qrcodegen_VERSION_MAX,
			                               qrcodegen_Mask_AUTO,
			                               FALSE);
		}
		if (!success)
			bzero (priv->qrcode, sizeof (priv->qrcode));
		g_object_notify (object, NMA_BAR_CODE_SIZE);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
nma_bar_code_init (NMABarCode *self)
{
}

/**
 * nma_bar_code_new:
 * @text: set the bar code text
 *
 * Returns: (transfer full): the bar code instance
 *
 * Since: 1.8.22
 */

NMABarCode *
nma_bar_code_new (const char *text)
{
	return g_object_new (NMA_TYPE_BAR_CODE, NMA_BAR_CODE_TEXT, text, NULL);
}

static void
nma_bar_code_class_init (NMABarCodeClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);

	object_class->get_property = get_property;
	object_class->set_property = set_property;

	g_object_class_install_property
		(object_class, PROP_TEXT,
		 g_param_spec_string (NMA_BAR_CODE_TEXT, "", "",
		                      "", G_PARAM_WRITABLE));

	g_object_class_install_property
		(object_class, PROP_SIZE,
		 g_param_spec_int (NMA_BAR_CODE_SIZE, "", "",
		                   G_MININT, G_MAXINT, 0, G_PARAM_READABLE));
}
