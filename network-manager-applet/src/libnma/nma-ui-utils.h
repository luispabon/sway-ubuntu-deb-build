// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2015 Red Hat, Inc.
 */

#ifndef NMA_UI_UTILS_H
#define NMA_UI_UTILS_H

#include <glib.h>
#include <gtk/gtk.h>
#include <NetworkManager.h>

void nma_utils_setup_password_storage (GtkWidget *passwd_entry,
                                       NMSettingSecretFlags initial_flags,
                                       NMSetting *setting,
                                       const char *password_flags_name,
                                       gboolean with_not_required,
                                       gboolean ask_mode);
NMSettingSecretFlags nma_utils_menu_to_secret_flags (GtkWidget *passwd_entry);
void nma_utils_update_password_storage (GtkWidget *passwd_entry,
                                        NMSettingSecretFlags secret_flags,
                                        NMSetting *setting,
                                        const char *password_flags_name);

#endif /* NMA_UI_UTILS_H */

