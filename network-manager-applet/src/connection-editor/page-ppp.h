// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2008 - 2014 Red Hat, Inc.
 */

#ifndef __PAGE_PPP_H__
#define __PAGE_PPP_H__

#include <glib.h>
#include <glib-object.h>

#include "ce-page.h"

#define CE_TYPE_PAGE_PPP            (ce_page_ppp_get_type ())
#define CE_PAGE_PPP(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_PPP, CEPagePpp))
#define CE_PAGE_PPP_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_PPP, CEPagePppClass))
#define CE_IS_PAGE_PPP(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_PPP))
#define CE_IS_PAGE_PPP_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_PAGE_PPP))
#define CE_PAGE_PPP_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_PPP, CEPagePppClass))

typedef struct {
	CEPage parent;
} CEPagePpp;

typedef struct {
	CEPageClass parent;
} CEPagePppClass;

GType ce_page_ppp_get_type (void);

CEPage *ce_page_ppp_new (NMConnectionEditor *editor,
                         NMConnection *connection,
                         GtkWindow *parent,
                         NMClient *client,
                         const char **out_secrets_setting_name,
                         GError **error);

#endif  /* __PAGE_PPP_H__ */
