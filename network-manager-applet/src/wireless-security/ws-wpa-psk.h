// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Applet -- allow user control over networking
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2007 - 2014 Red Hat, Inc.
 */

#ifndef WS_WPA_PSK_H
#define WS_WPA_PSK_H

typedef struct _WirelessSecurityWPAPSK WirelessSecurityWPAPSK;

WirelessSecurityWPAPSK * ws_wpa_psk_new (NMConnection *connection, gboolean secrets_only);

#endif /* WS_WEP_KEY_H */
