/* nma-bar-code-widget.h - Renderer of a "QR" code
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
#include "nma-bar-code-widget.h"

#define CARD_WIDTH_PT 252
#define CARD_HEIGHT_PT 144

struct _NMABarCodeWidget {
	GtkBox parent;
};

struct _NMABarCodeWidgetClass {
	GtkBoxClass parent_class;
};

typedef struct {
	NMConnection *connection;
	GtkWidget *qr_code;
	NMABarCode *qr;
} NMABarCodeWidgetPrivate;

/**
 * SECTION:nma-bar-code-widget
 * @title: NMABarCodeWidget
 *
 * This is a widget that displays a QR code for a connection suitable for
 * optical recognition, e.g. scanning on a phone to connect to a hotspot.
 */

G_DEFINE_TYPE_WITH_CODE (NMABarCodeWidget, nma_bar_code_widget, GTK_TYPE_BOX,
                         G_ADD_PRIVATE (NMABarCodeWidget))

enum {
	PROP_0,
	PROP_CONNECTION,

	LAST_PROP
};

#define NMA_BAR_CODE_WIDGET_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
                                     NMA_TYPE_BAR_CODE_WIDGET, \
                                     NMABarCodeWidgetPrivate))

static void
do_qr_code_draw (GtkDrawingArea *area, cairo_t *cr, int width, int height,
                 gpointer user_data)
{
	NMABarCodeWidgetPrivate *priv = NMA_BAR_CODE_WIDGET_GET_PRIVATE (user_data);
	int size = nma_bar_code_get_size (priv->qr);

	gtk_widget_set_size_request (priv->qr_code, (size + 2) * 3, (size + 2) * 3);

	cairo_set_source_rgba (cr, 1, 1, 1, 1);
	cairo_fill (cr);
	cairo_paint (cr);
	cairo_set_source_rgba (cr, 0, 0, 0, 1);
	cairo_scale (cr, (float)width / (size + 2), (float)height / (size + 2));
	cairo_translate (cr, 1, 1);
	cairo_set_antialias (cr, CAIRO_ANTIALIAS_NONE);
	nma_bar_code_draw (priv->qr, cr);
}

static gboolean
qr_code_draw (GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	do_qr_code_draw (GTK_DRAWING_AREA (widget), cr,
	                 gtk_widget_get_allocated_width (widget),
	                 gtk_widget_get_allocated_height (widget),
	                 user_data);

	return TRUE;
}

static char *
shell_escape (const char *to_escape)
{
	GString *string = g_string_sized_new (32);
	gboolean quote = *to_escape == '\0';
	const char *c;

	for (c = to_escape; *c; c++) {
		if (strchr ("$\\\"", *c))
			g_string_append_c (string, '\\');
		else if (!g_ascii_isalnum(*c) && !strchr ("@%^+-_[]:", *c))
			quote = TRUE;
		g_string_append_c (string, *c);
	}
	if (quote) {
		g_string_append_c (string, '"');
		g_string_prepend_c (string, '"');
	}
	return g_string_free (string, FALSE);
}

static void
draw_one (NMABarCodeWidget *self, cairo_t *cr,
          const char *psk, const char *ssid,
          const char *nmcli_line1, const char *nmcli_line2)
{
	NMABarCodeWidgetPrivate *priv = NMA_BAR_CODE_WIDGET_GET_PRIVATE (self);
	int size = nma_bar_code_get_size (priv->qr);

	cairo_save (cr);

	cairo_set_line_width (cr, 0.01);
	cairo_rectangle (cr, 0, 0, CARD_WIDTH_PT, CARD_HEIGHT_PT);
	cairo_stroke (cr);
	cairo_translate (cr, 12, 12);

	cairo_save (cr);
	cairo_scale (cr, (float)84/(float)size, (float)84/(float)size);
	cairo_set_antialias (cr, CAIRO_ANTIALIAS_NONE);
	nma_bar_code_draw (priv->qr, cr);
	cairo_restore (cr);

	cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);

	cairo_move_to (cr, 96, 12);
	cairo_set_font_size (cr, 12);
	cairo_show_text(cr, _("Network"));

	cairo_move_to (cr, 96, 30);
	cairo_set_font_size (cr, 16);
	cairo_show_text(cr, ssid);

	cairo_select_font_face(cr, "Monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);

	cairo_move_to (cr, 0, 108);
	cairo_set_font_size (cr, 10);
	cairo_show_text(cr, nmcli_line1);

	if (psk) {
		cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);

		cairo_move_to (cr, 96, 60);
		cairo_set_font_size (cr, 12);
		cairo_show_text(cr, _("Password"));

		cairo_move_to (cr, 96, 78);
		cairo_set_font_size (cr, 16);
		cairo_show_text(cr, psk);

		cairo_select_font_face(cr, "Monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);

		cairo_move_to (cr, 24, 120);
		cairo_set_font_size (cr, 10);
		cairo_show_text(cr, nmcli_line2);
	}

	cairo_restore (cr);
}

static void
draw_page (GtkPrintOperation *operation, GtkPrintContext *context, int page_nr, gpointer user_data)
{
	NMABarCodeWidget *self = NMA_BAR_CODE_WIDGET (user_data);
	NMABarCodeWidgetPrivate *priv = NMA_BAR_CODE_WIDGET_GET_PRIVATE (self);
	cairo_t *cr = gtk_print_context_get_cairo_context (context);
	double width = gtk_print_context_get_width (context);
	double height = gtk_print_context_get_height (context);
	int count_x = width / CARD_WIDTH_PT;
	int count_y = height / CARD_HEIGHT_PT;
	double spacing_x = (width - (count_x * CARD_WIDTH_PT)) / (count_x + 1);
	double spacing_y = (height - (count_y * CARD_HEIGHT_PT)) / (count_y + 1);
	NMSettingWireless *s_wireless;
	NMSettingWirelessSecurity *s_wsec;
	gs_free char *nmcli_line1 = NULL;
	gs_free char *nmcli_line2 = NULL;
	const char *psk = NULL;
	GBytes *ssid_bytes;
	char *ssid;
	char *tmp;
	int x, y;

	s_wireless = nm_connection_get_setting_wireless (priv->connection);
	if (!s_wireless) {
		nma_bar_code_set_text (priv->qr, NULL);
		gtk_widget_queue_draw (priv->qr_code);
		return;
	}

	ssid_bytes = nm_setting_wireless_get_ssid (s_wireless);
	g_return_if_fail (ssid_bytes);
	ssid = nm_utils_ssid_to_utf8 (g_bytes_get_data (ssid_bytes, NULL),
	                              g_bytes_get_size (ssid_bytes));
	g_return_if_fail (ssid);

	s_wsec = nm_connection_get_setting_wireless_security (priv->connection);
	if (s_wsec)
		psk = nm_setting_wireless_security_get_psk (s_wsec);

	tmp = shell_escape (ssid);
	nmcli_line1 = g_strdup_printf ("$ nmcli d wifi con %s%s", tmp, psk ? " \\" : "");
	g_free (tmp);

	if (psk) {
		tmp = shell_escape (psk);
		nmcli_line2 = g_strdup_printf ("password %s", tmp);
		g_free (tmp);
	}

	for (y = 0; y < count_y; y++) {
		cairo_save (cr);

		cairo_translate (cr, spacing_x, spacing_y);

		for (x = 0; x < count_x; x++) {
			draw_one (self, cr, psk, ssid, nmcli_line1, nmcli_line2);
			cairo_translate (cr, CARD_WIDTH_PT + spacing_x, 0);
		}

		cairo_restore (cr);
		cairo_translate (cr, 0, CARD_HEIGHT_PT + spacing_y);
	}
}

static gboolean
link_activated (GtkLabel *label, char *uri, gpointer user_data)
{
	NMABarCodeWidget *self = NMA_BAR_CODE_WIDGET (user_data);
	GtkPrintOperation *print = gtk_print_operation_new ();
	GtkWidget *window;
	GError *error = NULL;

	g_return_val_if_fail (strcmp (uri, "nma:print") == 0, FALSE);

	window = gtk_widget_get_ancestor (GTK_WIDGET (self), GTK_TYPE_WINDOW);

	gtk_print_operation_set_n_pages (print, 1);
	gtk_print_operation_set_use_full_page (print, TRUE);
	gtk_print_operation_set_unit (print, GTK_UNIT_POINTS);
	g_signal_connect (print, "draw_page", G_CALLBACK (draw_page), self);

	if (!gtk_print_operation_run (print, GTK_PRINT_OPERATION_ACTION_PRINT_DIALOG,
	                              window ? GTK_WINDOW (window) : NULL, &error)) {
		g_printerr ("%s", error->message);
		g_error_free (error);
	}

	g_object_unref (print);

	return FALSE;
}

static void
string_append_mecard (GString *string, const char *tag, const char *text)
{
	const char *p;
	bool is_hex = TRUE;
	int start;

	if (!text)
		return;

	g_string_append (string, tag);
	start = string->len;

	for (p = text; *p; p++) {
		if (!g_ascii_isxdigit (*p))
			is_hex = FALSE;
		if (strchr ("\\\":;,", *p))
			g_string_append_c (string, '\\');
		g_string_append_c (string, *p);
	}

	if (is_hex) {
		g_string_insert_c (string, start, '\"');
		g_string_append_c (string, '\"');
	}
	g_string_append_c (string, ';');
}

static void
update_qr_code (NMABarCodeWidget *self)
{
	NMABarCodeWidgetPrivate *priv = NMA_BAR_CODE_WIDGET_GET_PRIVATE (self);
	NMSettingWireless *s_wireless;
	NMSettingWirelessSecurity *s_wsec;
	const char *key_mgmt = NULL;
	const char *psk = NULL;
	const char *type = NULL;
	GBytes *ssid_bytes;
	char *ssid;
	GString *string;

	if (!priv->qr)
		return;

	s_wireless = nm_connection_get_setting_wireless (priv->connection);
	if (!s_wireless) {
		nma_bar_code_set_text (priv->qr, NULL);
		gtk_widget_queue_draw (priv->qr_code);
		return;
	}

	ssid_bytes = nm_setting_wireless_get_ssid (s_wireless);
	g_return_if_fail (ssid_bytes);
	ssid = nm_utils_ssid_to_utf8 (g_bytes_get_data (ssid_bytes, NULL),
	                              g_bytes_get_size (ssid_bytes));
	g_return_if_fail (ssid);

	string = g_string_sized_new (64);
	g_string_append (string, "WIFI:");

	s_wsec = nm_connection_get_setting_wireless_security (priv->connection);
	if (s_wsec) {
		key_mgmt = nm_setting_wireless_security_get_key_mgmt (s_wsec);
		psk = nm_setting_wireless_security_get_psk (s_wsec);
	}

	if (key_mgmt == NULL) {
		type = "nopass";
	} else if (   strcmp (key_mgmt, "none") == 0
	           || strcmp (key_mgmt, "ieee8021x") == 0) {
		type = "WEP";
	} else if (   strcmp (key_mgmt, "wpa-none") == 0
	           || strcmp (key_mgmt, "wpa-psk") == 0) {
		type = "WPA";
	}

	string_append_mecard(string, "T:", type);
	string_append_mecard(string, "S:", ssid);
	string_append_mecard(string, "P:", psk);

	if (nm_setting_wireless_get_hidden (s_wireless))
		g_string_append (string, "H:true;");

	g_string_append_c (string, ';');
	nma_bar_code_set_text (priv->qr, string->str);
	gtk_widget_queue_draw (priv->qr_code);
	g_string_free (string, TRUE);
}

static void
set_connection (NMABarCodeWidget *self, NMConnection *connection)
{
	NMABarCodeWidgetPrivate *priv = NMA_BAR_CODE_WIDGET_GET_PRIVATE (self);

	if (priv->connection) {
		g_signal_handlers_disconnect_by_data (priv->connection, self);
		g_clear_object (&priv->connection);
	}

	if (connection) {
		priv->connection = connection;
		g_signal_connect_swapped (connection, "changed", G_CALLBACK (update_qr_code), self);
		g_signal_connect_swapped (connection, "secrets-updated", G_CALLBACK (update_qr_code), self);
	}
}

static void
get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	NMABarCodeWidgetPrivate *priv = NMA_BAR_CODE_WIDGET_GET_PRIVATE (object);

	switch (prop_id) {
	case PROP_CONNECTION:
		g_value_set_object (value, priv->connection);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	NMABarCodeWidget *self = NMA_BAR_CODE_WIDGET (object);

	switch (prop_id) {
	case PROP_CONNECTION:
		set_connection (self, g_value_dup_object (value));
		update_qr_code (self);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
nma_bar_code_widget_init (NMABarCodeWidget *self)
{
	NMABarCodeWidgetPrivate *priv = NMA_BAR_CODE_WIDGET_GET_PRIVATE (self);

	gtk_widget_init_template (GTK_WIDGET (self));

	priv->qr = nma_bar_code_new (NULL);
	g_signal_connect (priv->qr_code, "draw", G_CALLBACK (qr_code_draw), self);
}

/**
 * nma_bar_code_widget_new:
 * @connection: connection to get network details from
 *
 * Returns: (transfer full): the bar code widget instance
 *
 * Since: 1.8.22
 */
GtkWidget *
nma_bar_code_widget_new (NMConnection *connection)
{
	return g_object_new (NMA_TYPE_BAR_CODE_WIDGET,
	                     NMA_BAR_CODE_WIDGET_CONNECTION, connection,
	                     NULL);
}

static void
finalize (GObject *object)
{
	NMABarCodeWidget *self = NMA_BAR_CODE_WIDGET (object);
	NMABarCodeWidgetPrivate *priv = NMA_BAR_CODE_WIDGET_GET_PRIVATE (self);

	g_clear_object (&priv->qr);
	set_connection (self, NULL);

	G_OBJECT_CLASS (nma_bar_code_widget_parent_class)->finalize (object);
}

static void
nma_bar_code_widget_class_init (NMABarCodeWidgetClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	object_class->get_property = get_property;
	object_class->set_property = set_property;
	object_class->finalize = finalize;

	g_object_class_install_property
		(object_class, PROP_CONNECTION,
		 g_param_spec_object (NMA_BAR_CODE_WIDGET_CONNECTION, "", "",
		                      NM_TYPE_CONNECTION,
		                      G_PARAM_READABLE | G_PARAM_WRITABLE));

	gtk_widget_class_set_template_from_resource (widget_class,
	                                             "/org/freedesktop/network-manager-applet/nma-bar-code-widget.ui");

	gtk_widget_class_bind_template_child_private (widget_class, NMABarCodeWidget, qr_code);
	gtk_widget_class_bind_template_callback (widget_class, link_activated);
}
