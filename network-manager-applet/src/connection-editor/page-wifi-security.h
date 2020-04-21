// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2008 - 2014 Red Hat, Inc.
 */

#ifndef __PAGE_WIFI_SECURITY_H__
#define __PAGE_WIFI_SECURITY_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>

#include "ce-page.h"

#define CE_TYPE_PAGE_WIFI_SECURITY            (ce_page_wifi_security_get_type ())
#define CE_PAGE_WIFI_SECURITY(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_WIFI_SECURITY, CEPageWifiSecurity))
#define CE_PAGE_WIFI_SECURITY_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_WIFI_SECURITY, CEPageWifiSecurityClass))
#define CE_IS_PAGE_WIFI_SECURITY(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_WIFI_SECURITY))
#define CE_IS_PAGE_WIFI_SECURITY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_PAGE_WIFI_SECURITY))
#define CE_PAGE_WIFI_SECURITY_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_WIFI_SECURITY, CEPageWifiSecurityClass))

typedef struct {
	CEPage parent;
} CEPageWifiSecurity;

typedef struct {
	CEPageClass parent;
} CEPageWifiSecurityClass;

GType ce_page_wifi_security_get_type (void);

CEPage *ce_page_wifi_security_new (NMConnectionEditor *editor,
                                   NMConnection *connection,
                                   GtkWindow *parent,
                                   NMClient *client,
                                   const char **out_secrets_setting_name,
                                   GError **error);

#endif  /* __PAGE_WIFI_SECURITY_H__ */

