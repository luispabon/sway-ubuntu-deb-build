// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Applet -- allow user control over networking
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2009 - 2014 Red Hat, Inc.
 */

#include "nm-default.h"
#include "nma-private.h"
#include "helpers.h"

void
helper_fill_secret_entry (NMConnection *connection,
                          GtkBuilder *builder,
                          const char *entry_name,
                          GType setting_type,
                          HelperSecretFunc func)
{
	GtkWidget *widget;
	NMSetting *setting;
	const char *tmp;

	g_return_if_fail (connection != NULL);
	g_return_if_fail (builder != NULL);
	g_return_if_fail (entry_name != NULL);
	g_return_if_fail (func != NULL);

	setting = nm_connection_get_setting (connection, setting_type);
	if (setting) {
		tmp = (*func) (setting);
		if (tmp) {
			widget = GTK_WIDGET (gtk_builder_get_object (builder, entry_name));
			g_assert (widget);
			gtk_editable_set_text (GTK_EDITABLE (widget), tmp);
		}
	}
}

