// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2013 Jiri Pirko <jiri@resnulli.us>
 * Copyright 2013 - 2014  Red Hat, Inc.
 */

#ifndef __PAGE_TEAM_PORT_H__
#define __PAGE_TEAM_PORT_H__

#include <glib.h>
#include <glib-object.h>

#include "ce-page.h"

#define CE_TYPE_PAGE_TEAM_PORT            (ce_page_team_port_get_type ())
#define CE_PAGE_TEAM_PORT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_TEAM_PORT, CEPageTeamPort))
#define CE_PAGE_TEAM_PORT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_TEAM_PORT, CEPageTeamPortClass))
#define CE_IS_PAGE_TEAM_PORT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_TEAM_PORT))
#define CE_IS_PAGE_TEAM_PORT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_PAGE_TEAM_PORT))
#define CE_PAGE_TEAM_PORT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_TEAM_PORT, CEPageTeamPortClass))

typedef struct {
	CEPage parent;
} CEPageTeamPort;

typedef struct {
	CEPageClass parent;
} CEPageTeamPortClass;

GType ce_page_team_port_get_type (void);

CEPage *ce_page_team_port_new (NMConnectionEditor *editor,
                               NMConnection *connection,
                               GtkWindow *parent,
                               NMClient *client,
                               const char **out_secrets_setting_name,
                               GError **error);

#endif  /* __PAGE_TEAM_PORT_H__ */

