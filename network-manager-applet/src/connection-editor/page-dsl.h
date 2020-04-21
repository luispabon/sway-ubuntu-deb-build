// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2008 - 2014 Red Hat, Inc.
 */

#ifndef __PAGE_DSL_H__
#define __PAGE_DSL_H__

#include <glib.h>
#include <glib-object.h>

#include "ce-page.h"

#define CE_TYPE_PAGE_DSL            (ce_page_dsl_get_type ())
#define CE_PAGE_DSL(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_DSL, CEPageDsl))
#define CE_PAGE_DSL_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_DSL, CEPageDslClass))
#define CE_IS_PAGE_DSL(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_DSL))
#define CE_IS_PAGE_DSL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_PAGE_DSL))
#define CE_PAGE_DSL_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_DSL, CEPageDslClass))

typedef struct {
	CEPage parent;
} CEPageDsl;

typedef struct {
	CEPageClass parent;
} CEPageDslClass;

GType ce_page_dsl_get_type (void);

CEPage *ce_page_dsl_new (NMConnectionEditor *editor,
                         NMConnection *connection,
                         GtkWindow *parent,
                         NMClient *client,
                         const char **out_secrets_setting_name,
                         GError **error);

void dsl_connection_new (FUNC_TAG_PAGE_NEW_CONNECTION_IMPL,
                         GtkWindow *parent,
                         const char *detail,
                         gpointer detail_data,
                         NMConnection *connection,
                         NMClient *client,
                         PageNewConnectionResultFunc callback,
                         gpointer user_data);

#endif  /* __PAGE_DSL_H__ */
