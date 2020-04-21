// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Applet -- allow user control over networking
 *
 * Lubomir Rintel <lkundrak@v3.sk>
 *
 * Copyright (C) 2019 Red Hat, Inc.
 */

#ifndef NMA_PRIVATE_H

#if !GTK_CHECK_VERSION(3,96,0)
#define gtk_editable_set_text(editable,text)             gtk_entry_set_text(GTK_ENTRY(editable), (text))
#define gtk_editable_get_text(editable)                  gtk_entry_get_text(GTK_ENTRY(editable))
#define gtk_editable_set_width_chars(editable, n_chars)  gtk_entry_set_width_chars(GTK_ENTRY(editable), (n_chars))
#endif

void nma_gtk_widget_activate_default (GtkWidget *widget);

#define NMA_PRIVATE_H

#endif /* NMA_PRIVATE_H */
