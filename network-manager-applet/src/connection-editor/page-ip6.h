// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2008 - 2014 Red Hat, Inc.
 */

#ifndef __PAGE_IP6_H__
#define __PAGE_IP6_H__

#include <glib.h>
#include <glib-object.h>

#include "ce-page.h"

#define CE_TYPE_PAGE_IP6            (ce_page_ip6_get_type ())
#define CE_PAGE_IP6(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_IP6, CEPageIP6))
#define CE_PAGE_IP6_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_IP6, CEPageIP6Class))
#define CE_IS_PAGE_IP6(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_IP6))
#define CE_IS_PAGE_IP6_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_PAGE_IP6))
#define CE_PAGE_IP6_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_IP6, CEPageIP6Class))

typedef struct {
	CEPage parent;
} CEPageIP6;

typedef struct {
	CEPageClass parent;
} CEPageIP6Class;

GType ce_page_ip6_get_type (void);

CEPage *ce_page_ip6_new (NMConnectionEditor *editor,
                         NMConnection *connection,
                         GtkWindow *parent,
                         NMClient *client,
                         const char **out_secrets_setting_name,
                         GError **error);

#endif  /* __PAGE_IP6_H__ */

