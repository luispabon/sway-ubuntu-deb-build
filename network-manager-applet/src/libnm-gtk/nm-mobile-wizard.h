// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * (C) Copyright 2008 - 2011 Red Hat, Inc.
 */

#ifndef MOBILE_WIZARD_H
#define MOBILE_WIZARD_H

#include <glib.h>
#include <NetworkManager.h>
#include <nm-device.h>

typedef struct NMAMobileWizard NMAMobileWizard;

typedef struct {
	char *provider_name;
	char *plan_name;
	NMDeviceModemCapabilities devtype;
	char *username;
	char *password;
	char *gsm_apn;
} NMAMobileWizardAccessMethod;

typedef void (*NMAMobileWizardCallback) (NMAMobileWizard *self,
										 gboolean canceled,
										 NMAMobileWizardAccessMethod *method,
										 gpointer user_data);

NMAMobileWizard *nma_mobile_wizard_new (GtkWindow *parent,
										GtkWindowGroup *window_group,
										NMDeviceModemCapabilities modem_caps,
										gboolean will_connect_after,
										NMAMobileWizardCallback cb,
										gpointer user_data);

void nma_mobile_wizard_present (NMAMobileWizard *wizard);

void nma_mobile_wizard_destroy (NMAMobileWizard *self);

#endif /* MOBILE_WIZARD_H */

