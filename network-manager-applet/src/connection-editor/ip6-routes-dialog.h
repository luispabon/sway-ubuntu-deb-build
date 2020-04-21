// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2008 - 2014 Red Hat, Inc.
 */

#ifndef IP6_ROUTES_DIALOG_H
#define IP6_ROUTES_DIALOG_H

#include <glib.h>
#include <gtk/gtk.h>

#include <NetworkManager.h>

#include "nm-setting-ip6-config.h"

GtkWidget *ip6_routes_dialog_new (NMSettingIPConfig *s_ip6, gboolean automatic);

void ip6_routes_dialog_update_setting (GtkWidget *dialog, NMSettingIPConfig *s_ip6);

#endif /* IP6_ROUTES_DIALOG_H */
