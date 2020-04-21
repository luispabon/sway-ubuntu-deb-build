// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Copyright 2016 Red Hat, Inc.
 */

#ifndef __PAGE_IP_TUNNEL_H__
#define __PAGE_IP_TUNNEL_H__

#include <glib.h>
#include <glib-object.h>

#include "ce-page.h"

#define CE_TYPE_PAGE_IP_TUNNEL            (ce_page_ip_tunnel_get_type ())
#define CE_PAGE_IP_TUNNEL(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_IP_TUNNEL, CEPageIPTunnel))
#define CE_PAGE_IP_TUNNEL_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_IP_TUNNEL, CEPageIPTunnelClass))
#define CE_IS_PAGE_IP_TUNNEL(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_IP_TUNNEL))
#define CE_IS_PAGE_IP_TUNNEL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_PAGE_IP_TUNNEL))
#define CE_PAGE_IP_TUNNEL_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_IP_TUNNEL, CEPageIPTunnelClass))

typedef struct {
	CEPage parent;
} CEPageIPTunnel;

typedef struct {
	CEPageClass parent;
} CEPageIPTunnelClass;

GType ce_page_ip_tunnel_get_type (void);

CEPage *ce_page_ip_tunnel_new (NMConnectionEditor *editor,
                               NMConnection *connection,
                               GtkWindow *parent,
                               NMClient *client,
                               const char **out_secrets_setting_name,
                               GError **error);

void ip_tunnel_connection_new (FUNC_TAG_PAGE_NEW_CONNECTION_IMPL,
                               GtkWindow *parent,
                               const char *detail,
                               gpointer detail_data,
                               NMConnection *connection,
                               NMClient *client,
                               PageNewConnectionResultFunc callback,
                               gpointer user_data);

#endif  /* __PAGE_IP_TUNNEL_H__ */
