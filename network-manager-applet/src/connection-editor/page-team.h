// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2013 Jiri Pirko <jiri@resnulli.us>
 * Copyright 2013 - 2014  Red Hat, Inc.
 */

#ifndef __PAGE_TEAM_H__
#define __PAGE_TEAM_H__

#include <glib.h>
#include <glib-object.h>

#include "page-master.h"

#define CE_TYPE_PAGE_TEAM            (ce_page_team_get_type ())
#define CE_PAGE_TEAM(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_TEAM, CEPageTeam))
#define CE_PAGE_TEAM_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_TEAM, CEPageTeamClass))
#define CE_IS_PAGE_TEAM(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_TEAM))
#define CE_IS_PAGE_TEAM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_PAGE_TEAM))
#define CE_PAGE_TEAM_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_TEAM, CEPageTeamClass))

typedef struct {
	CEPageMaster parent;
} CEPageTeam;

typedef struct {
	CEPageMasterClass parent;
} CEPageTeamClass;

GType ce_page_team_get_type (void);

CEPage *ce_page_team_new (NMConnectionEditor *editor,
                          NMConnection *connection,
                          GtkWindow *parent,
                          NMClient *client,
                          const char **out_secrets_setting_name,
                          GError **error);

void team_connection_new (FUNC_TAG_PAGE_NEW_CONNECTION_IMPL,
                          GtkWindow *parent,
                          const char *detail,
                          gpointer detail_data,
                          NMConnection *connection,
                          NMClient *client,
                          PageNewConnectionResultFunc result_func,
                          gpointer user_data);

#endif  /* __PAGE_TEAM_H__ */

