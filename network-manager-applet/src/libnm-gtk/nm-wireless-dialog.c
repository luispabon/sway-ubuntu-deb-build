// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Applet -- allow user control over networking
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * (C) Copyright 2007 - 2012 Red Hat, Inc.
 */

#include "nm-default.h"

#include <nm-client.h>

#include "nm-wireless-dialog.h"
#include "nm-wifi-dialog.h"

GType
nma_wireless_dialog_get_type (void)
{
	return nma_wifi_dialog_get_type ();
}

NMConnection *
nma_wireless_dialog_get_connection (NMAWirelessDialog *self,
                                    NMDevice **out_device,
                                    NMAccessPoint **ap)
{
	return nma_wifi_dialog_get_connection ((NMAWifiDialog *)self, out_device, ap);
}

GtkWidget *
nma_wireless_dialog_new (NMClient *client,
                         NMRemoteSettings *settings,
                         NMConnection *connection,
                         NMDevice *device,
                         NMAccessPoint *ap,
                         gboolean secrets_only)
{
	return nma_wifi_dialog_new (client, settings, connection, device, ap, secrets_only);
}

GtkWidget *
nma_wireless_dialog_new_for_other (NMClient *client, NMRemoteSettings *settings)
{
	return nma_wifi_dialog_new_for_hidden (client, settings);
}

GtkWidget *
nma_wireless_dialog_new_for_create (NMClient *client, NMRemoteSettings *settings)
{
	return nma_wifi_dialog_new_for_create (client, settings);
}

