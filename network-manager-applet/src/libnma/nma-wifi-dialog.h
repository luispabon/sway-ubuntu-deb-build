// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Wireless Applet -- Display wireless access points and allow user control
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2007 - 2014 Red Hat, Inc.
 */

#ifndef NMA_WIFI_DIALOG_H
#define NMA_WIFI_DIALOG_H

#include <gtk/gtk.h>
#include <glib.h>
#include <glib-object.h>

#include <NetworkManager.h>

#include "nma-version.h"

#define NMA_TYPE_WIFI_DIALOG            (nma_wifi_dialog_get_type ())
#define NMA_WIFI_DIALOG(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), NMA_TYPE_WIFI_DIALOG, NMAWifiDialog))
#define NMA_WIFI_DIALOG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), NMA_TYPE_WIFI_DIALOG, NMAWifiDialogClass))
#define NMA_IS_WIFI_DIALOG(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), NMA_TYPE_WIFI_DIALOG))
#define NMA_IS_WIFI_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), NMA_TYPE_WIFI_DIALOG))
#define NMA_WIFI_DIALOG_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), NMA_TYPE_WIFI_DIALOG, NMAWifiDialogClass))

typedef struct {
	GtkDialog parent;
} NMAWifiDialog;

typedef struct {
	GtkDialogClass parent;
} NMAWifiDialogClass;

GType nma_wifi_dialog_get_type (void);

GtkWidget *nma_wifi_dialog_new (NMClient *client,
                                NMConnection *connection,
                                NMDevice *device,
                                NMAccessPoint *ap,
                                gboolean secrets_only);

GtkWidget *nma_wifi_dialog_new_for_secrets (NMClient *client,
                                            NMConnection *connection,
                                            const char *secrets_setting_name,
                                            const char *const*secrets_hints);

GtkWidget *nma_wifi_dialog_new_for_hidden (NMClient *client);

GtkWidget *nma_wifi_dialog_new_for_create (NMClient *client);

NMConnection * nma_wifi_dialog_get_connection (NMAWifiDialog *self,
                                               NMDevice **device,
                                               NMAccessPoint **ap);

NMA_DEPRECATED_IN_1_2
GtkWidget * nma_wifi_dialog_nag_user (NMAWifiDialog *self);

NMA_DEPRECATED_IN_1_2
void nma_wifi_dialog_set_nag_ignored (NMAWifiDialog *self, gboolean ignored);

NMA_DEPRECATED_IN_1_2
gboolean nma_wifi_dialog_get_nag_ignored (NMAWifiDialog *self);

NMA_DEPRECATED_IN_1_2_FOR(nma_wifi_dialog_new_for_hidden)
GtkWidget *nma_wifi_dialog_new_for_other (NMClient *client);

#endif	/* NMA_WIFI_DIALOG_H */

