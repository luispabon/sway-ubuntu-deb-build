// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Wireless Applet -- Display wireless access points and allow user control
 *
 * (C) Copyright 2007 - 2015 Red Hat, Inc.
 */

#ifndef NMA_UI_UTILS_H
#define NMA_UI_UTILS_H

#include <glib.h>
#include <gtk/gtk.h>
#include <nm-device.h>
#include <nm-setting.h>
#include <nm-connection.h>

const char *nma_utils_get_device_vendor (NMDevice *device);
const char *nma_utils_get_device_product (NMDevice *device);
const char *nma_utils_get_device_description (NMDevice *device);
const char *nma_utils_get_device_generic_type_name (NMDevice *device);
const char *nma_utils_get_device_type_name (NMDevice *device);

char **nma_utils_disambiguate_device_names (NMDevice **devices,
                                            int        num_devices);
char *nma_utils_get_connection_device_name (NMConnection *connection);

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

