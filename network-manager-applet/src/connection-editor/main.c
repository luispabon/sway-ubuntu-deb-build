// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Rodrigo Moya <rodrigo@gnome-db.org>
 *
 * Copyright 2004 - 2018 Red Hat, Inc.
 */

#include "nm-default.h"

#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include <glib-unix.h>

#include "nm-connection-list.h"
#include "nm-connection-editor.h"
#include "connection-helpers.h"
#include "vpn-helpers.h"

#define CONNECTION_LIST_TAG "nm-connection-list"

gboolean nm_ce_keep_above;

/*************************************************/

static void
editor_created (NMConnectionList *list, gpointer user_data)
{
	g_application_release (G_APPLICATION (user_data));
}

static gboolean
handle_arguments (GApplication *application,
                  const char *type,
                  gboolean create,
                  gboolean show,
                  const char *edit_uuid,
                  const char *import)
{
	NMConnectionList *list = g_object_get_data (G_OBJECT (application), CONNECTION_LIST_TAG);
	gboolean show_list = TRUE;
	GType ctype = 0;
	gs_free char *type_tmp = NULL;
	const char *p, *detail = NULL;

	if (type) {
		p = strchr (type, ':');
		if (p) {
			type = type_tmp = g_strndup (type, p - type);
			detail = p + 1;
		}
		ctype = nm_setting_lookup_type (type);
		if (ctype == 0 && !p) {
			gs_free char *service_type = NULL;

			/* allow using the VPN name directly, without "vpn:" prefix. */
			service_type = nm_vpn_plugin_info_list_find_service_type (vpn_get_plugin_infos (), type);
			if (service_type) {
				ctype = NM_TYPE_SETTING_VPN;
				detail = type;
			}
		}
		if (ctype == 0) {
			g_warning ("Unknown connection type '%s'", type);
			return TRUE;
		}
	}

	if (show) {
		/* Just show the given connection type page */
		nm_connection_list_set_type (list, ctype);
	} else if (create) {
		g_application_hold (application);
		if (!ctype)
			nm_connection_list_add (list, editor_created, application);
		else
			nm_connection_list_create (list, ctype, detail, NULL,
			                           editor_created, application);
		show_list = FALSE;
	} else if (import) {
		/* import */
		g_application_hold (application);
		nm_connection_list_create (list, ctype, detail, import,
		                           editor_created, application);
		show_list = FALSE;
	} else if (edit_uuid) {
		/* Show the edit dialog for the given UUID */
		nm_connection_list_edit (list, edit_uuid);
		show_list = FALSE;
	}

	return show_list;
}

static gboolean
signal_handler (gpointer user_data)
{
	GApplication *application = G_APPLICATION (user_data);

	g_message ("Caught signal shutting down...");
	g_application_quit (application);

	return G_SOURCE_REMOVE;
}

static void
create_activated (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	GApplication *application = G_APPLICATION (user_data);

	handle_arguments (application, NULL, TRUE, FALSE, NULL, NULL);
}

static void
quit_activated (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	GApplication *application = G_APPLICATION (user_data);

	g_application_quit (application);
}

static GActionEntry app_entries[] =
{
	{ "create", create_activated, NULL, NULL, NULL },
	{ "quit", quit_activated, NULL, NULL, NULL },
};

static void
new_editor_cb (NMConnectionList *list, NMConnectionEditor *new_editor, gpointer user_data)
{
	GtkApplication *app = GTK_APPLICATION (user_data);

	gtk_application_add_window (app, nm_connection_editor_get_window (new_editor));
}

static void
list_visible_cb (NMConnectionList *list, GParamSpec *pspec, gpointer user_data)
{
	GtkApplication *app = GTK_APPLICATION (user_data);

	if (gtk_widget_get_visible (GTK_WIDGET (list)))
		gtk_application_add_window (app, GTK_WINDOW (list));
	else
		gtk_application_remove_window (app, GTK_WINDOW (list));
}

static void
editor_startup (GApplication *application, gpointer user_data)
{
	GtkApplication *app = GTK_APPLICATION (application);
	NMConnectionList *list;

	g_action_map_add_action_entries (G_ACTION_MAP (app), app_entries,
	                                 G_N_ELEMENTS (app_entries), app);

	list = nm_connection_list_new ();
	if (!list) {
		g_warning ("Failed to initialize the UI, exiting...");
		g_application_quit (application);
		return;
	}

	g_object_set_data_full (G_OBJECT (application), CONNECTION_LIST_TAG, g_object_ref (list), g_object_unref);
	g_signal_connect_object (list, NM_CONNECTION_LIST_NEW_EDITOR, G_CALLBACK (new_editor_cb), application, 0);
	g_signal_connect_object (list, "notify::visible", G_CALLBACK (list_visible_cb), application, 0);
	g_signal_connect (list, "delete-event", G_CALLBACK (gtk_widget_hide_on_delete), NULL);
}

static void
editor_activate (GApplication *application, gpointer user_data)
{
	NMConnectionList *list = g_object_get_data (G_OBJECT (application), CONNECTION_LIST_TAG);

	nm_connection_list_present (list);
}

static gint
editor_command_line (GApplication *application,
                     GApplicationCommandLine *command_line,
                     gpointer user_data)
{
	gchar **argv;
	gint argc;
	GOptionContext *opt_ctx = NULL;
	GError *error = NULL;
	gs_free char *type = NULL, *uuid = NULL, *import = NULL;
	gboolean create = FALSE, show = FALSE;
	int ret = 1;
	GOptionEntry entries[] = {
		{ "type",   't', 0, G_OPTION_ARG_STRING, &type,   "Type of connection to show or create", NM_SETTING_WIRED_SETTING_NAME },
		{ "create", 'c', 0, G_OPTION_ARG_NONE,   &create, "Create a new connection", NULL },
		{ "show",   's', 0, G_OPTION_ARG_NONE,   &show,   "Show a given connection type page", NULL },
		{ "edit",   'e', 0, G_OPTION_ARG_STRING, &uuid,   "Edit an existing connection with a given UUID", "UUID" },
		{ "import", 'i', 0, G_OPTION_ARG_STRING, &import, "Import a VPN connection from given file", NULL },
		{ NULL }
	};

	argv = g_application_command_line_get_arguments (command_line, &argc);

	opt_ctx = g_option_context_new (NULL);
	g_option_context_set_summary (opt_ctx, "Allows users to view and edit network connection settings");
	g_option_context_add_main_entries (opt_ctx, entries, NULL);
	if (!g_option_context_parse (opt_ctx, &argc, &argv, &error)) {
		g_application_command_line_printerr (command_line, "Failed to parse options: %s\n", error->message);
		g_error_free (error);
		goto out;
	}

	/* Just one page for both CDMA & GSM, handle that here */
	if (g_strcmp0 (type, NM_SETTING_CDMA_SETTING_NAME) == 0) {
		g_free (type);
		type = g_strdup (NM_SETTING_GSM_SETTING_NAME);
	}

	if (handle_arguments (application, type, create, show, uuid, import))
		g_application_activate (application);

	ret = 0;

out:
	g_option_context_free (opt_ctx);
	return ret;
}

int
main (int argc, char *argv[])
{
	gs_unref_object GtkApplication *app = NULL;
	GOptionContext *opt_ctx;
	GOptionEntry entries[] = {
		/* This is not passed over D-Bus. */
		{ "keep-above", 0, G_OPTION_FLAG_HIDDEN, G_OPTION_ARG_NONE, &nm_ce_keep_above, NULL, NULL },
		{ NULL }
	};

	bindtextdomain (GETTEXT_PACKAGE, NMALOCALEDIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);

	app = gtk_application_new ("org.gnome.nm_connection_editor",
	                           G_APPLICATION_HANDLES_COMMAND_LINE);

	opt_ctx = g_option_context_new (NULL);
	g_option_context_add_main_entries (opt_ctx, entries, NULL);
	g_option_context_set_help_enabled (opt_ctx, FALSE);
	g_option_context_set_ignore_unknown_options (opt_ctx, TRUE);
	g_option_context_parse (opt_ctx, &argc, &argv, NULL);
	g_option_context_free (opt_ctx);

	g_signal_connect (app, "startup", G_CALLBACK (editor_startup), NULL);
	g_signal_connect (app, "activate", G_CALLBACK (editor_activate), NULL);
	g_signal_connect (app, "command-line", G_CALLBACK (editor_command_line), NULL);

	g_unix_signal_add (SIGTERM, signal_handler, app);
	g_unix_signal_add (SIGINT, signal_handler, app);

	return g_application_run (G_APPLICATION (app), argc, argv);
}
