// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2013 - 2014 Red Hat, Inc.
 */

#ifndef __PAGE_DCB_H__
#define __PAGE_DCB_H__

#include <glib.h>
#include <glib-object.h>

#include "ce-page.h"

#define CE_TYPE_PAGE_DCB            (ce_page_dcb_get_type ())
#define CE_PAGE_DCB(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_DCB, CEPageDcb))
#define CE_PAGE_DCB_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_DCB, CEPageDcbClass))
#define CE_IS_PAGE_DCB(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_DCB))
#define CE_IS_PAGE_DCB_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_PAGE_DCB))
#define CE_PAGE_DCB_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_DCB, CEPageDcbClass))

typedef struct {
	CEPage parent;
} CEPageDcb;

typedef struct {
	CEPageClass parent;
} CEPageDcbClass;

GType ce_page_dcb_get_type (void);

CEPage *ce_page_dcb_new (NMConnectionEditor *editor,
                         NMConnection *connection,
                         GtkWindow *parent,
                         NMClient *client,
                         const char **out_secrets_setting_name,
                         GError **error);

#endif  /* __PAGE_DCB_H__ */
