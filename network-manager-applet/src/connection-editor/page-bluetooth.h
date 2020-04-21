// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Lubomir Rintel <lkundrak@v3.sk>
 *
 * Copyright 2014 Red Hat, Inc.
 */

#ifndef __PAGE_BLUETOOTH_H__
#define __PAGE_BLUETOOTH_H__

#include <NetworkManager.h>

#include <glib.h>
#include <glib-object.h>

#include "ce-page.h"

#define CE_TYPE_PAGE_BLUETOOTH            (ce_page_bluetooth_get_type ())
#define CE_PAGE_BLUETOOTH(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_PAGE_BLUETOOTH, CEPageBluetooth))
#define CE_PAGE_BLUETOOTH_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_PAGE_BLUETOOTH, CEPageBluetoothClass))
#define CE_IS_PAGE_BLUETOOTH(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_PAGE_BLUETOOTH))
#define CE_IS_PAGE_BLUETOOTH_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_PAGE_BLUETOOTH))
#define CE_PAGE_BLUETOOTH_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_PAGE_BLUETOOTH, CEPageBluetoothClass))

typedef struct {
	CEPage parent;
} CEPageBluetooth;

typedef struct {
	CEPageClass parent;
} CEPageBluetoothClass;

GType ce_page_bluetooth_get_type (void);

CEPage *ce_page_bluetooth_new (NMConnectionEditor *edit,
                               NMConnection *connection,
                               GtkWindow *parent,
                               NMClient *client,
                               const char **out_secrets_setting_name,
                               GError **error);

void bluetooth_connection_new (FUNC_TAG_PAGE_NEW_CONNECTION_IMPL,
                               GtkWindow *parent,
                               const char *detail,
                               gpointer detail_data,
                               NMConnection *connection,
                               NMClient *client,
                               PageNewConnectionResultFunc result_func,
                               gpointer user_data);

#endif  /* __PAGE_BLUETOOTH_H__ */
