// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2009 - 2017 Red Hat, Inc.
 */

#ifndef __CE_POLKIT_H__
#define __CE_POLKIT_H__

#include <gtk/gtk.h>

#include <NetworkManager.h>

void ce_polkit_connect_widget (GtkWidget *widget,
                               const char *tooltip,
                               const char *auth_tooltip,
                               NMClient *client,
                               NMClientPermission permission);

void ce_polkit_set_widget_validation_error (GtkWidget *widget,
                                            const char *validation_error);

#endif  /* __CE_POLKIT_H__ */
