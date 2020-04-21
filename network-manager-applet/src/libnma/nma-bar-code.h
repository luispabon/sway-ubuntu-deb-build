/* nma-bar-code.h - Widget that renders a "QR" code
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
 * Copyright (C) 2018, 2019 Red Hat, Inc.
 */

#ifndef __NMA_BAR_CODE_H__
#define __NMA_BAR_CODE_H__

#include <glib-object.h>
#include <cairo.h>

#include "nma-version.h"

#define NMA_TYPE_BAR_CODE            (nma_bar_code_get_type ())
#define NMA_BAR_CODE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), NMA_TYPE_BAR_CODE, NMABarCode))
#define NMA_BAR_CODE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), NMA_TYPE_BAR_CODE, NMABarCodeClass))
#define NMA_IS_BAR_CODE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), NMA_TYPE_BAR_CODE))
#define NMA_IS_BAR_CODE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), NMA_TYPE_BAR_CODE))
#define NMA_BAR_CODE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), NMA_TYPE_BAR_CODE, NMABarCodeClass))

#define NMA_BAR_CODE_TEXT "text"
#define NMA_BAR_CODE_SIZE "size"

typedef struct _NMABarCode       NMABarCode;
typedef struct _NMABarCodeClass  NMABarCodeClass;

NMA_AVAILABLE_IN_1_8_22
GType       nma_bar_code_get_type (void) G_GNUC_CONST;

NMA_AVAILABLE_IN_1_8_22
NMABarCode *nma_bar_code_new (const char *text);

NMA_AVAILABLE_IN_1_8_22
void        nma_bar_code_set_text (NMABarCode *self, const char *text);

NMA_AVAILABLE_IN_1_8_22
int         nma_bar_code_get_size (NMABarCode *self);

NMA_AVAILABLE_IN_1_8_22
void        nma_bar_code_draw (NMABarCode *self, cairo_t *cr);

#endif /* __NMA_BAR_CODE_H__ */
