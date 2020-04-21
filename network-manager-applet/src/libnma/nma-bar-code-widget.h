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

#ifndef __NMA_BAR_CODE_WIDGET_H__
#define __NMA_BAR_CODE_WIDGET_H__

#include <glib-object.h>

#include "nma-version.h"

#define NMA_TYPE_BAR_CODE_WIDGET            (nma_bar_code_widget_get_type ())
#define NMA_BAR_CODE_WIDGET(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), NMA_TYPE_BAR_CODE_WIDGET, NMABarCodeWidget))
#define NMA_BAR_CODE_WIDGET_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), NMA_TYPE_BAR_CODE_WIDGET, NMABarCodeWidgetClass))
#define NMA_IS_BAR_CODE_WIDGET(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), NMA_TYPE_BAR_CODE_WIDGET))
#define NMA_IS_BAR_CODE_WIDGET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), NMA_TYPE_BAR_CODE_WIDGET))
#define NMA_BAR_CODE_WIDGET_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), NMA_TYPE_BAR_CODE_WIDGET, NMABarCodeWidgetClass))

#define NMA_BAR_CODE_WIDGET_CONNECTION "connection"

typedef struct _NMABarCodeWidget       NMABarCodeWidget;
typedef struct _NMABarCodeWidgetClass  NMABarCodeWidgetClass;

NMA_AVAILABLE_IN_1_8_22
GType       nma_bar_code_widget_get_type (void) G_GNUC_CONST;

NMA_AVAILABLE_IN_1_8_22
GtkWidget  *nma_bar_code_widget_new (NMConnection *connection);

#endif /* __NMA_BAR_CODE_WIDGET_H__ */
