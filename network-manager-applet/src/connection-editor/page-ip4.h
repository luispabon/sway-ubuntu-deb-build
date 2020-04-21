// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2008 - 2014 Red Hat, Inc.
 */

#ifndef __PAGE_IP4_H__
#define __PAGE_IP4_H__

#include <glib.h>
#include <glib-object.h>

#include "ce-page.h"

#define CE_TYPE_PAGE_IP4            (ce_page_ip4_get_type ())
#define CE_PAGE_IP4(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_IP4, CEPageIP4))
#define CE_PAGE_IP4_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_IP4, CEPageIP4Class))
#define CE_IS_PAGE_IP4(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_IP4))
#define CE_IS_PAGE_IP4_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_PAGE_IP4))
#define CE_PAGE_IP4_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_IP4, CEPageIP4Class))

typedef struct {
	CEPage parent;
} CEPageIP4;

typedef struct {
	CEPageClass parent;
} CEPageIP4Class;

GType ce_page_ip4_get_type (void);

CEPage *ce_page_ip4_new (NMConnectionEditor *editor,
                         NMConnection *connection,
                         GtkWindow *parent,
                         NMClient *client,
                         const char **out_secrets_setting_name,
                         GError **error);

#endif  /* __PAGE_IP4_H__ */

