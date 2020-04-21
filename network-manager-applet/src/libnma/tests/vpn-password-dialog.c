// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2018 Red Hat, Inc.
 */

#include "nm-default.h"

#include <gtk/gtk.h>
#include "nma-vpn-password-dialog.h"

int
main (int argc, char *argv[])
{
	GtkWidget *widget;

#if GTK_CHECK_VERSION(3,90,0)
	gtk_init ();
#else
	gtk_init (&argc, &argv);
#endif

	widget = nma_vpn_password_dialog_new ("Title", "Message", "Password");

	nma_vpn_password_dialog_set_password (NMA_VPN_PASSWORD_DIALOG (widget), "Password One");
	nma_vpn_password_dialog_set_password_label (NMA_VPN_PASSWORD_DIALOG (widget), "First _Label");

	nma_vpn_password_dialog_set_password_secondary (NMA_VPN_PASSWORD_DIALOG (widget), "");
	nma_vpn_password_dialog_set_password_secondary_label (NMA_VPN_PASSWORD_DIALOG (widget), "_Second Label");
	nma_vpn_password_dialog_set_show_password_secondary (NMA_VPN_PASSWORD_DIALOG (widget), TRUE);

	nma_vpn_password_dialog_set_password_ternary_label (NMA_VPN_PASSWORD_DIALOG (widget), "_Third Label");
	nma_vpn_password_dialog_set_show_password_ternary (NMA_VPN_PASSWORD_DIALOG (widget), TRUE);

	nma_vpn_password_dialog_run_and_block (NMA_VPN_PASSWORD_DIALOG (widget));
	gtk_widget_destroy (widget);
}
