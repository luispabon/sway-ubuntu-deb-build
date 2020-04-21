// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Copyright 2012 - 2014 Red Hat, Inc.
 */

#ifndef __PAGE_INFINIBAND_H__
#define __PAGE_INFINIBAND_H__

#include <glib.h>
#include <glib-object.h>

#include "ce-page.h"

#define CE_TYPE_PAGE_INFINIBAND            (ce_page_infiniband_get_type ())
#define CE_PAGE_INFINIBAND(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_INFINIBAND, CEPageInfiniband))
#define CE_PAGE_INFINIBAND_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_INFINIBAND, CEPageInfinibandClass))
#define CE_IS_PAGE_INFINIBAND(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_INFINIBAND))
#define CE_IS_PAGE_INFINIBAND_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_PAGE_INFINIBAND))
#define CE_PAGE_INFINIBAND_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_INFINIBAND, CEPageInfinibandClass))

typedef struct {
	CEPage parent;
} CEPageInfiniband;

typedef struct {
	CEPageClass parent;
} CEPageInfinibandClass;

GType ce_page_infiniband_get_type (void);

CEPage *ce_page_infiniband_new (NMConnectionEditor *editor,
                                NMConnection *connection,
                                GtkWindow *parent,
                                NMClient *client,
                                const char **out_secrets_setting_name,
                                GError **error);

void infiniband_connection_new (FUNC_TAG_PAGE_NEW_CONNECTION_IMPL,
                                GtkWindow *parent,
                                const char *detail,
                                gpointer detail_data,
                                NMConnection *connection,
                                NMClient *client,
                                PageNewConnectionResultFunc result_func,
                                gpointer user_data);

#endif  /* __PAGE_INFINIBAND_H__ */

