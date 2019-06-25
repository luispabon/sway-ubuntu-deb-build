/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Copyright 2018 Red Hat, Inc.
 */

#include "nm-default.h"

#include <gtk/gtk.h>
#include "nma-vpn-password-dialog.h"

int
main (int argc, char *argv[])
{
	GtkWidget *widget;

	gtk_init (&argc, &argv);

	widget = nma_vpn_password_dialog_new ("Title", "Message", "Password");

	nma_vpn_password_dialog_set_password (NMA_VPN_PASSWORD_DIALOG (widget), "Password One");
	nma_vpn_password_dialog_set_password_label (NMA_VPN_PASSWORD_DIALOG (widget), "First _Label");

	nma_vpn_password_dialog_set_password_secondary (NMA_VPN_PASSWORD_DIALOG (widget), "Password Two");
	nma_vpn_password_dialog_set_password_secondary_label (NMA_VPN_PASSWORD_DIALOG (widget), "_Second Label");
	nma_vpn_password_dialog_set_show_password_secondary (NMA_VPN_PASSWORD_DIALOG (widget), TRUE);

	nma_vpn_password_dialog_set_password_ternary (NMA_VPN_PASSWORD_DIALOG (widget), "Password Three");
	nma_vpn_password_dialog_set_password_ternary_label (NMA_VPN_PASSWORD_DIALOG (widget), "_Third Label");
	nma_vpn_password_dialog_set_show_password_ternary (NMA_VPN_PASSWORD_DIALOG (widget), TRUE);

	nma_vpn_password_dialog_run_and_block (NMA_VPN_PASSWORD_DIALOG (widget));
	gtk_widget_destroy (widget);
}
