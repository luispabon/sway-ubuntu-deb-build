// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2008 - 2014 Red Hat, Inc.
 */

#ifndef __PAGE_ETHERNET_H__
#define __PAGE_ETHERNET_H__

#include <glib.h>
#include <glib-object.h>

#include "ce-page.h"

#define CE_TYPE_PAGE_ETHERNET            (ce_page_ethernet_get_type ())
#define CE_PAGE_ETHERNET(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_ETHERNET, CEPageEthernet))
#define CE_PAGE_ETHERNET_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_ETHERNET, CEPageEthernetClass))
#define CE_IS_PAGE_ETHERNET(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_ETHERNET))
#define CE_IS_PAGE_ETHERNET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_PAGE_ETHERNET))
#define CE_PAGE_ETHERNET_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_ETHERNET, CEPageEthernetClass))

typedef struct {
	CEPage parent;
} CEPageEthernet;

typedef struct {
	CEPageClass parent;
} CEPageEthernetClass;

GType ce_page_ethernet_get_type (void);

CEPage *ce_page_ethernet_new (NMConnectionEditor *editor,
                              NMConnection *connection,
                              GtkWindow *parent,
                              NMClient *client,
                              const char **out_secrets_setting_name,
                              GError **error);

void ethernet_connection_new (FUNC_TAG_PAGE_NEW_CONNECTION_IMPL,
                              GtkWindow *parent,
                              const char *detail,
                              gpointer detail_data,
                              NMConnection *connection,
                              NMClient *client,
                              PageNewConnectionResultFunc result_func,
                              gpointer user_data);

#endif  /* __PAGE_ETHERNET_H__ */

