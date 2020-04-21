// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2008 - 2014 Red Hat, Inc.
 */

#ifndef __PAGE_WIFI_H__
#define __PAGE_WIFI_H__

#include <glib.h>
#include <glib-object.h>

#include "ce-page.h"

#define CE_TYPE_PAGE_WIFI            (ce_page_wifi_get_type ())
#define CE_PAGE_WIFI(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_WIFI, CEPageWifi))
#define CE_PAGE_WIFI_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_WIFI, CEPageWifiClass))
#define CE_IS_PAGE_WIFI(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_WIFI))
#define CE_IS_PAGE_WIFI_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_PAGE_WIFI))
#define CE_PAGE_WIFI_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_WIFI, CEPageWifiClass))

typedef struct {
	CEPage parent;
} CEPageWifi;

typedef struct {
	CEPageClass parent;
} CEPageWifiClass;

GType ce_page_wifi_get_type (void);

CEPage *ce_page_wifi_new (NMConnectionEditor *editor,
                          NMConnection *connection,
                          GtkWindow *parent,
                          NMClient *client,
                          const char **out_secrets_setting_name,
                          GError **error);

/* Caller must free returned value with g_bytes_unref() */
GBytes *ce_page_wifi_get_ssid (CEPageWifi *self);


void wifi_connection_new (FUNC_TAG_PAGE_NEW_CONNECTION_IMPL,
                          GtkWindow *parent,
                          const char *detail,
                          gpointer detail_data,
                          NMConnection *connection,
                          NMClient *client,
                          PageNewConnectionResultFunc result_func,
                          gpointer user_data);

#endif  /* __PAGE_WIFI_H__ */

