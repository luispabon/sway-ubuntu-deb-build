// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2008 - 2014 Red Hat, Inc.
 */

#ifndef IP4_ROUTES_DIALOG_H
#define IP4_ROUTES_DIALOG_H

#include <glib.h>
#include <gtk/gtk.h>

#include <NetworkManager.h>

#include "nm-setting-ip4-config.h"

GtkWidget *ip4_routes_dialog_new (NMSettingIPConfig *s_ip4, gboolean automatic);

void ip4_routes_dialog_update_setting (GtkWidget *dialog, NMSettingIPConfig *s_ip4);

#endif /* IP4_ROUTES_DIALOG_H */
