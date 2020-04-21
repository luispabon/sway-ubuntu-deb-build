// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Applet -- allow user control over networking
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2007 - 2014 Red Hat, Inc.
 */

#ifndef WS_LEAP_H
#define WS_LEAP_H

typedef struct _WirelessSecurityLEAP WirelessSecurityLEAP;

WirelessSecurityLEAP * ws_leap_new (NMConnection *connection, gboolean secrets_only);

#endif /* WS_LEAP_H */
