// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2007 - 2019 Red Hat, Inc.
 */

#ifndef WS_SAE_H
#define WS_SAE_H

/* For compatibility with NetworkManager-1.20 and earlier. */
#define NMU_SEC_SAE 9

typedef struct _WirelessSecuritySAE WirelessSecuritySAE;

WirelessSecuritySAE * ws_sae_new (NMConnection *connection, gboolean secrets_only);

#endif /* WS_SAE_H */
