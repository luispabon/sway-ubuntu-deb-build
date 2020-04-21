/*
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
 * Copyright 2019 Red Hat, Inc.
 */

#include "nm-default.h"

#include <gtk/gtk.h>
#include "nma-cert-chooser.h"

int
main (int argc, char *argv[])
{
	GtkWidget *dialog;
	GtkBox *content;
	GtkWidget *widget;

#if GTK_CHECK_VERSION(3,90,0)
	gtk_init ();
#else
	gtk_init (&argc, &argv);
#endif

	dialog = gtk_dialog_new_with_buttons ("NMACertChooser test",
	                                      NULL, GTK_DIALOG_MODAL,
	                                      "Dismiss",  GTK_RESPONSE_DELETE_EVENT,
	                                      NULL);
	content = GTK_BOX (gtk_dialog_get_content_area (GTK_DIALOG (dialog)));
#if GTK_CHECK_VERSION(3,90,0)
	gtk_box_set_spacing (content, 6);
#endif

	widget = nma_cert_chooser_new ("Any", 0);
	gtk_widget_show (widget);
#if GTK_CHECK_VERSION(3,90,0)
	gtk_container_add (GTK_CONTAINER (content), widget);
#else
	gtk_box_pack_start (content, widget, TRUE, TRUE, 6);
#endif

	widget = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	gtk_widget_show (widget);
#if GTK_CHECK_VERSION(3,90,0)
	gtk_container_add (GTK_CONTAINER (content), widget);
#else
	gtk_box_pack_start (content, widget, TRUE, TRUE, 6);
#endif

	widget = nma_cert_chooser_new ("FLAG_PASSWORDS", NMA_CERT_CHOOSER_FLAG_PASSWORDS);
	nma_cert_chooser_set_cert (NMA_CERT_CHOOSER (widget),
	                           "pkcs11:object=praise;type=satan",
	                           NM_SETTING_802_1X_CK_SCHEME_PKCS11);
	nma_cert_chooser_set_key_uri (NMA_CERT_CHOOSER (widget),
	                              "pkcs11:object=worship;type=doom");
	gtk_widget_show (widget);
#if GTK_CHECK_VERSION(3,90,0)
	gtk_container_add (GTK_CONTAINER (content), widget);
#else
	gtk_box_pack_start (content, widget, TRUE, TRUE, 6);
#endif

	widget = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	gtk_widget_show (widget);
#if GTK_CHECK_VERSION(3,90,0)
	gtk_container_add (GTK_CONTAINER (content), widget);
#else
	gtk_box_pack_start (content, widget, TRUE, TRUE, 6);
#endif

	widget = nma_cert_chooser_new ("FLAG_CERT", NMA_CERT_CHOOSER_FLAG_CERT);
	gtk_widget_show (widget);
#if GTK_CHECK_VERSION(3,90,0)
	gtk_container_add (GTK_CONTAINER (content), widget);
#else
	gtk_box_pack_start (content, widget, TRUE, TRUE, 6);
#endif

	widget = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	gtk_widget_show (widget);
#if GTK_CHECK_VERSION(3,90,0)
	gtk_container_add (GTK_CONTAINER (content), widget);
#else
	gtk_box_pack_start (content, widget, TRUE, TRUE, 6);
#endif

	widget = nma_cert_chooser_new ("FLAG_PEM", NMA_CERT_CHOOSER_FLAG_PEM);
	gtk_widget_show (widget);
#if GTK_CHECK_VERSION(3,90,0)
	gtk_container_add (GTK_CONTAINER (content), widget);
#else
	gtk_box_pack_start (content, widget, TRUE, TRUE, 6);
#endif

	gtk_dialog_run (GTK_DIALOG (dialog));
}
