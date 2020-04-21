// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Applet -- allow user control over networking
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2007 - 2014 Red Hat, Inc.
 */

#ifndef WS_WPA_EAP_H
#define WS_WPA_EAP_H

typedef struct _WirelessSecurityWPAEAP WirelessSecurityWPAEAP;

WirelessSecurityWPAEAP * ws_wpa_eap_new (NMConnection *connection,
                                         gboolean is_editor,
                                         gboolean secrets_only,
                                         const char *const*secrets_hints);

#endif /* WS_WPA_EAP_H */
