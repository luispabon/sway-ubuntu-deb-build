// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2018 Red Hat, Inc.
 */

#include "nm-default.h"

#include <gtk/gtk.h>
#include <NetworkManager.h>
#include "nma-wifi-dialog.h"

static void
response_cb (GtkDialog *obj, gint response, gpointer user_data)
{
	NMAWifiDialog *dialog = NMA_WIFI_DIALOG (obj);

	g_print ("response %i\n", response);

	if (response == GTK_RESPONSE_OK) {
		GHashTable *diff = NULL, *setting_diff;
		GHashTableIter iter, setting_iter;
		const char *setting, *key;
		NMConnection *connection = nma_wifi_dialog_get_connection (dialog, NULL, NULL);
		NMConnection *orig = user_data;

		g_print ("settings changed:\n");
		nm_connection_diff (connection, orig, NM_SETTING_COMPARE_FLAG_EXACT, &diff);
		if (!diff)
			return;

		g_hash_table_iter_init (&iter, diff);
		while (g_hash_table_iter_next (&iter, (gpointer) &setting, (gpointer) &setting_diff)) {
			g_hash_table_iter_init (&setting_iter, setting_diff);
			while (g_hash_table_iter_next (&setting_iter, (gpointer) &key, NULL))
				g_print (" %s.%s\n", setting, key);
		}

		g_hash_table_destroy (diff);
	}
}

int
main (int argc, char *argv[])
{
	GtkWidget *dialog;
	NMClient *client = NULL;
	NMConnection *connection = NULL;
	GError *error = NULL;
	gs_unref_bytes GBytes *ssid = g_bytes_new_static ("<Maj Vaj Faj>", 13);
	const char *hints[] = {
		NM_SETTING_802_1X_IDENTITY,
		NM_SETTING_802_1X_PASSWORD,
		NM_SETTING_802_1X_PRIVATE_KEY_PASSWORD,
		NULL
	};

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

	dialog = nma_wifi_dialog_new_for_secrets (client,
	                                          nm_simple_connection_new_clone (connection),
	                                          NM_SETTING_802_1X_SETTING_NAME,
	                                          hints);
	g_signal_connect (dialog, "response", G_CALLBACK (response_cb), connection);
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);

	g_object_unref (connection);
}
