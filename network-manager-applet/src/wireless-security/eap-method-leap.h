// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Applet -- allow user control over networking
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * (C) Copyright 2007 - 2010 Red Hat, Inc.
 */

#ifndef EAP_METHOD_LEAP_H
#define EAP_METHOD_LEAP_H

#include "wireless-security.h"

typedef struct _EAPMethodLEAP EAPMethodLEAP;

EAPMethodLEAP *eap_method_leap_new (WirelessSecurity *ws_parent,
                                    NMConnection *connection,
                                    gboolean secrets_only);

#endif /* EAP_METHOD_LEAP_H */

