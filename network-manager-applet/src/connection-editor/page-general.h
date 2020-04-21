// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Copyright 2012 - 2014 Red Hat, Inc.
 */

#ifndef __PAGE_GENERAL_H__
#define __PAGE_GENERAL_H__

#include <glib.h>
#include <glib-object.h>

#include "ce-page.h"

#define CE_TYPE_PAGE_GENERAL            (ce_page_general_get_type ())
#define CE_PAGE_GENERAL(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_GENERAL, CEPageGeneral))
#define CE_PAGE_GENERAL_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_GENERAL, CEPageGeneralClass))
#define CE_IS_PAGE_GENERAL(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_GENERAL))
#define CE_IS_PAGE_GENERAL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_PAGE_GENERAL))
#define CE_PAGE_GENERAL_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_GENERAL, CEPageGeneralClass))

typedef struct {
	CEPage parent;
} CEPageGeneral;

typedef struct {
	CEPageClass parent;
} CEPageGeneralClass;

GType ce_page_general_get_type (void);

CEPage *ce_page_general_new (NMConnectionEditor *editor,
                             NMConnection *connection,
                             GtkWindow *parent,
                             NMClient *client,
                             const char **out_secrets_setting_name,
                             GError **error);

#endif  /* __PAGE_GENERAL_H__ */

