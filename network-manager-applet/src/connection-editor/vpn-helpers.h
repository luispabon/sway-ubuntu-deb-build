// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2008 - 2014 Red Hat, Inc.
 */

#ifndef _VPN_HELPERS_H_
#define _VPN_HELPERS_H_

#include <glib.h>
#include <gtk/gtk.h>

#include <NetworkManager.h>

GSList *vpn_get_plugin_infos (void);

NMVpnEditorPlugin *vpn_get_plugin_by_service (const char *service);

void vpn_export (NMConnection *connection);

gboolean vpn_supports_ipv6 (NMConnection *connection);

#endif  /* _VPN_HELPERS_H_ */
