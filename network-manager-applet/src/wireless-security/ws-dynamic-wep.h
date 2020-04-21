// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Applet -- allow user control over networking
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2007 - 2014 Red Hat, Inc.
 */

#ifndef WS_DYNAMIC_WEP_H
#define WS_DYNAMIC_WEP_H

typedef struct _WirelessSecurityDynamicWEP WirelessSecurityDynamicWEP;

WirelessSecurityDynamicWEP *ws_dynamic_wep_new (NMConnection *connection,
                                                gboolean is_editor,
                                                gboolean secrets_only);

#endif /* WS_DYNAMIC_WEP_H */
