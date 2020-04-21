// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * (C) Copyright 2008 Red Hat, Inc.
 */

#ifndef PPP_AUTH_METHODS_DIALOG_H
#define PPP_AUTH_METHODS_DIALOG_H

#include <glib.h>
#include <gtk/gtk.h>

GtkWidget *ppp_auth_methods_dialog_new (gboolean refuse_eap,
                                        gboolean refuse_pap,
                                        gboolean refuse_chap,
                                        gboolean refuse_mschap,
                                        gboolean refuse_mschapv2);

void ppp_auth_methods_dialog_get_methods (GtkWidget *dialog,
                                          gboolean *refuse_eap,
                                          gboolean *refuse_pap,
                                          gboolean *refuse_chap,
                                          gboolean *refuse_mschap,
                                          gboolean *refuse_mschapv2);

#endif /* PPP_AUTH_METHODS_DIALOG_H */
