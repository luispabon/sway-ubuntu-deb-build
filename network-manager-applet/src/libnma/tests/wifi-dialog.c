// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2018 Red Hat, Inc.
 */

#include "nm-default.h"

#include <gtk/gtk.h>
#include "nma-wifi-dialog.h"

int
main (int argc, char *argv[])
{
	GtkWidget *dialog;
	NMClient *client = NULL;
	NMConnection *connection = NULL;
	NMDevice *device = NULL;
	NMAccessPoint *ap = NULL;
	gboolean secrets_only = FALSE;
	GError *error = NULL;
	gs_unref_bytes GBytes *ssid = g_bytes_new_static ("<Maj Vaj Faj>", 13);

#if GTK_CHECK_VERSION(3,90,0)
	gtk_init ();
#else
	gtk_init (&argc, &argv);
#endif

	client = nm_client_new (NULL, NULL);
	connection = nm_simple_connection_new ();
	nm_connection_add_setting (connection,
		g_object_new (NM_TYPE_SETTING_CONNECTION,
		              NM_SETTING_CONNECTION_ID, "<Maj Vaj Faj>",
		              NULL));
	nm_connection_add_setting (connection,
		g_object_new (NM_TYPE_SETTING_WIRELESS,
		              NM_SETTING_WIRELESS_SSID, ssid,
		              NULL));
	nm_connection_add_setting (connection,
		g_object_new (NM_TYPE_SETTING_WIRELESS_SECURITY,
		              NM_SETTING_WIRELESS_SECURITY_KEY_MGMT, "wpa-eap",
		              NULL));
	nm_connection_add_setting (connection,
		g_object_new (NM_TYPE_SETTING_802_1X,
		              NM_SETTING_802_1X_EAP, (const char * const []){ "peap", NULL },
		              NM_SETTING_802_1X_IDENTITY, "budulinek",
		              NM_SETTING_802_1X_PHASE2_AUTH, "gtc",
		              NULL));

	if (!nm_connection_normalize (connection, NULL, NULL, &error)) {
		nm_connection_dump (connection);
		g_printerr ("Error: %s\n", error->message);
		g_error_free (error);
		return 1;
	}

	dialog = nma_wifi_dialog_new (client, connection, device, ap, secrets_only);
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}
