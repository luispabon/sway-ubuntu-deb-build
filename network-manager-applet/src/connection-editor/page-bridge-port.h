// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2008 - 2014 Red Hat, Inc.
 */

#ifndef __PAGE_BRIDGE_PORT_H__
#define __PAGE_BRIDGE_PORT_H__

#include <glib.h>
#include <glib-object.h>

#include "ce-page.h"

#define CE_TYPE_PAGE_BRIDGE_PORT            (ce_page_bridge_port_get_type ())
#define CE_PAGE_BRIDGE_PORT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_BRIDGE_PORT, CEPageBridgePort))
#define CE_PAGE_BRIDGE_PORT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_BRIDGE_PORT, CEPageBridgePortClass))
#define CE_IS_PAGE_BRIDGE_PORT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_BRIDGE_PORT))
#define CE_IS_PAGE_BRIDGE_PORT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_PAGE_BRIDGE_PORT))
#define CE_PAGE_BRIDGE_PORT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_BRIDGE_PORT, CEPageBridgePortClass))

typedef struct {
	CEPage parent;
} CEPageBridgePort;

typedef struct {
	CEPageClass parent;
} CEPageBridgePortClass;

GType ce_page_bridge_port_get_type (void);

CEPage *ce_page_bridge_port_new (NMConnectionEditor *editor,
                                 NMConnection *connection,
                                 GtkWindow *parent,
                                 NMClient *client,
                                 const char **out_secrets_setting_name,
                                 GError **error);

#endif  /* __PAGE_BRIDGE_PORT_H__ */

