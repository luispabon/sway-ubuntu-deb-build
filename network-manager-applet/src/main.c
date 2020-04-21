// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Applet -- allow user control over networking
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * This applet used the GNOME Wireless Applet as a skeleton to build from.
 *
 * (C) Copyright 2005 Red Hat, Inc.
 */

#include "nm-default.h"

#include <string.h>
#include <stdlib.h>

#include "applet.h"

gboolean shell_debug = FALSE;
gboolean with_agent = TRUE;
gboolean with_appindicator = FALSE;

static void
usage (const char *progname)
{
	gs_free char *basename = g_path_get_basename (progname);

	fprintf (stdout, "%s %s\n\n%s\n%s\n\n",
	                 _("Usage:"),
	                 basename,
	                 _("This program is a component of NetworkManager (https://wiki.gnome.org/Projects/NetworkManager/)."),
	                 _("It is not intended for command-line interaction but instead runs in the GNOME desktop environment."));
}

int main (int argc, char *argv[])
{
	GApplication *applet;
	char *fake_args[1] = { argv[0] };
	guint32 i;
	int status;

	for (i = 1; i < argc; i++) {
		if (!strcmp (argv[i], "--help")) {
			usage (argv[0]);
			exit (0);
		}
		if (!strcmp (argv[i], "--shell-debug"))
			shell_debug = TRUE;
		else if (!strcmp (argv[i], "--no-agent"))
			with_agent = FALSE;
		else if (!strcmp (argv[i], "--indicator")) {
#ifdef WITH_APPINDICATOR
			with_appindicator = TRUE;
#else
			g_error ("Error: --indicator requested but indicator support not available");
#endif
		}
	}

	bindtextdomain (GETTEXT_PACKAGE, NMALOCALEDIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	if (!with_appindicator)
		gdk_set_allowed_backends ("x11,*");
	gtk_init (&argc, &argv);
	textdomain (GETTEXT_PACKAGE);

	applet = g_object_new (NM_TYPE_APPLET,
	                       "application-id", "org.freedesktop.network-manager-applet",
	                       NULL);
	status = g_application_run (applet, 1, fake_args);
	g_object_unref (applet);

	return status;
}

