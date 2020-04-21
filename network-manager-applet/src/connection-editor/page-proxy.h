// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * (C) Copyright 2016 Atul Anand <atulhjp@gmail.com>.
 */

#ifndef __PAGE_PROXY_H__
#define __PAGE_PROXY_H__

#include "ce-page.h"

#define CE_TYPE_PAGE_PROXY            (ce_page_proxy_get_type ())
#define CE_PAGE_PROXY(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_PROXY, CEPageProxy))
#define CE_PAGE_PROXY_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_PROXY, CEPageProxyClass))
#define CE_IS_PAGE_PROXY(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_PROXY))
#define CE_IS_PAGE_PROXY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_PAGE_PROXY))
#define CE_PAGE_PROXY_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_PROXY, CEPageProxyClass))

typedef struct {
	CEPage parent;
} CEPageProxy;

typedef struct {
	CEPageClass parent;
} CEPageProxyClass;

GType ce_page_proxy_get_type (void);

CEPage *ce_page_proxy_new (NMConnectionEditor *editor,
                           NMConnection *connection,
                           GtkWindow *parent,
                           NMClient *client,
                           const char **out_secrets_setting_name,
                           GError **error);

#endif  /* __PAGE_PROXY_H__ */
