// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Copyright 2008 - 2014 Red Hat, Inc.
 */

#ifndef __PAGE_VLAN_H__
#define __PAGE_VLAN_H__

#include <glib.h>
#include <glib-object.h>

#include "ce-page.h"

#define CE_TYPE_PAGE_VLAN            (ce_page_vlan_get_type ())
#define CE_PAGE_VLAN(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_VLAN, CEPageVlan))
#define CE_PAGE_VLAN_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_VLAN, CEPageVlanClass))
#define CE_IS_PAGE_VLAN(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_VLAN))
#define CE_IS_PAGE_VLAN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((obj), CE_TYPE_PAGE_VLAN))
#define CE_PAGE_VLAN_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_VLAN, CEPageVlanClass))

typedef struct {
	CEPage parent;
} CEPageVlan;

typedef struct {
	CEPageClass parent;
} CEPageVlanClass;

GType ce_page_vlan_get_type (void);

CEPage *ce_page_vlan_new (NMConnectionEditor *editor,
                          NMConnection *connection,
                          GtkWindow *parent,
                          NMClient *client,
                          const char **out_secrets_setting_name,
                          GError **error);

void vlan_connection_new (FUNC_TAG_PAGE_NEW_CONNECTION_IMPL,
                          GtkWindow *parent,
                          const char *detail,
                          gpointer detail_data,
                          NMConnection *connection,
                          NMClient *client,
                          PageNewConnectionResultFunc result_func,
                          gpointer user_data);

#endif  /* __PAGE_VLAN_H__ */

