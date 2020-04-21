// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Copyright 2017 Red Hat, Inc.
 */

#ifndef __PAGE_MACSEC_H__
#define __PAGE_MACSEC_H__

#include <glib.h>
#include <glib-object.h>

#include "ce-page.h"

#define CE_TYPE_PAGE_MACSEC            (ce_page_macsec_get_type ())
#define CE_PAGE_MACSEC(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_MACSEC, CEPageMacsec))
#define CE_PAGE_MACSEC_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_MACSEC, CEPageMacsecClass))
#define CE_IS_PAGE_MACSEC(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_MACSEC))
#define CE_IS_PAGE_MACSEC_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_PAGE_MACSEC))
#define CE_PAGE_MACSEC_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_MACSEC, CEPageMacsecClass))

typedef struct {
	CEPage parent;
} CEPageMacsec;

typedef struct {
	CEPageClass parent;
} CEPageMacsecClass;

GType ce_page_macsec_get_type (void);

CEPage *ce_page_macsec_new (NMConnectionEditor *editor,
                            NMConnection *connection,
                            GtkWindow *parent,
                            NMClient *client,
                            const char **out_secrets_setting_name,
                            GError **error);

void macsec_connection_new (FUNC_TAG_PAGE_NEW_CONNECTION_IMPL,
                            GtkWindow *parent,
                            const char *detail,
                            gpointer detail_data,
                            NMConnection *connection,
                            NMClient *client,
                            PageNewConnectionResultFunc callback,
                            gpointer user_data);

#endif  /* __PAGE_MACSEC_H__ */
