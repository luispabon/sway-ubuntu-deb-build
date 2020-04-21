// SPDX-License-Identifier: GPL-2.0+
/* vim: set ft=c ts=4 sts=4 sw=4 noexpandtab smartindent: */

/* EAP-FAST authentication method (RFC4851)
 *
 * (C) Copyright 2012 Red Hat, Inc.
 */

#ifndef EAP_METHOD_FAST_H
#define EAP_METHOD_FAST_H

#include "wireless-security.h"

typedef struct _EAPMethodFAST EAPMethodFAST;

EAPMethodFAST *eap_method_fast_new (WirelessSecurity *ws_parent,
                                    NMConnection *connection,
                                    gboolean is_editor,
                                    gboolean secrets_only);

#endif /* EAP_METHOD_FAST_H */

