/*
 * run-vpn - VPN plugin runner for testing
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * (C) Copyright 2018 Lubomir Rintel
 */

#include "nm-default.h"

#include <NetworkManager.h>
#include <gtk/gtk.h>
#include <stdlib.h>

static gboolean
window_deleted (GtkWidget *widget,
                GdkEvent *event,
                gpointer user_data)
{
	GMainLoop *main_loop = user_data;
	g_main_loop_quit (main_loop);
	return TRUE;
}

int
main (int argc, char *argv[])
{
	gs_unref_object NMVpnEditorPlugin *plugin = NULL;
	gs_unref_object NMVpnEditor *editor = NULL;
	gs_unref_object NMConnection *connection = NULL;
	gs_free char *service_type = NULL;
	GMainLoop *main_loop;
	GtkWidget *window;
	GtkWidget *widget;
	gs_free_error GError *error = NULL;

	gtk_init (&argc, &argv);
	if (argc != 2) {
		g_printerr ("Usage: %s libnm-vpn-plugin-<name>.so\n", argv[0]);
		return EXIT_FAILURE;
	}

	plugin = nm_vpn_editor_plugin_load (argv[1], NULL, &error);
	if (!plugin) {
		g_printerr ("Error: %s\n", error->message);
		return EXIT_FAILURE;
	}

	g_object_get (G_OBJECT (plugin), "service", &service_type, NULL);
	g_return_val_if_fail (service_type, EXIT_FAILURE);

	connection = nm_simple_connection_new ();
	nm_connection_add_setting (connection,
		g_object_new (NM_TYPE_SETTING_VPN,
		              "service-type", service_type,
		              NULL));

	editor = nm_vpn_editor_plugin_get_editor (plugin, connection, &error);
	if (!editor) {
		g_printerr ("Error: %s\n", error->message);
		return EXIT_FAILURE;
	}

	main_loop = g_main_loop_new (NULL, FALSE);
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_widget_show (window);
	g_signal_connect (G_OBJECT (window), "delete-event", G_CALLBACK (window_deleted), main_loop);

	widget = GTK_WIDGET (nm_vpn_editor_get_widget (editor));
	gtk_widget_show (widget);
	gtk_container_add (GTK_CONTAINER (window), widget);
	g_main_loop_run (main_loop);

	if (!nm_vpn_editor_update_connection (editor, connection, &error)) {
		g_printerr ("Error: %s\n", error->message);
		return EXIT_FAILURE;
	}

	gtk_widget_destroy (widget);
	nm_connection_dump (connection);

	return EXIT_SUCCESS;
}
