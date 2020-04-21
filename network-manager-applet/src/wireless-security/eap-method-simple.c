// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Applet -- allow user control over networking
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2007 - 2014 Red Hat, Inc.
 */

#include "nm-default.h"
#include "nma-private.h"

#include <ctype.h>
#include <string.h>

#include "eap-method.h"
#include "wireless-security.h"
#include "helpers.h"
#include "nma-ui-utils.h"
#include "utils.h"

struct _EAPMethodSimple {
	EAPMethod parent;

	WirelessSecurity *ws_parent;

	const char *password_flags_name;
	EAPMethodSimpleType type;
	EAPMethodSimpleFlags flags;

	gboolean username_requested;
	gboolean password_requested;
	gboolean pkey_passphrase_requested;
	GtkEntry *username_entry;
	GtkEntry *password_entry;
	GtkToggleButton *show_password;
	GtkEntry *pkey_passphrase_entry;
	GtkToggleButton *show_pkey_passphrase;
	guint idle_func_id;
};

static void
show_password_toggled_cb (GtkToggleButton *button, EAPMethodSimple *method)
{
	gboolean visible;

	visible = gtk_toggle_button_get_active (button);
	gtk_entry_set_visibility (method->password_entry, visible);
}

static void
show_pkey_passphrase_toggled_cb (GtkToggleButton *button, EAPMethodSimple *method)
{
	gboolean visible;

	visible = gtk_toggle_button_get_active (button);
	gtk_entry_set_visibility (method->pkey_passphrase_entry, visible);
}

static gboolean
always_ask_selected (GtkEntry *passwd_entry)
{
	return !!(  nma_utils_menu_to_secret_flags (GTK_WIDGET (passwd_entry))
	          & NM_SETTING_SECRET_FLAG_NOT_SAVED);
}

static gboolean
validate (EAPMethod *parent, GError **error)
{
	EAPMethodSimple *method = (EAPMethodSimple *)parent;
	const char *text;
	gboolean ret = TRUE;

	if (method->username_requested) {
		text = gtk_editable_get_text (GTK_EDITABLE (method->username_entry));
		if (!text || !strlen (text)) {
			widget_set_error (GTK_WIDGET (method->username_entry));
			g_set_error_literal (error, NMA_ERROR, NMA_ERROR_GENERIC, _("missing EAP username"));
			ret = FALSE;
		} else
			widget_unset_error (GTK_WIDGET (method->username_entry));
	}

	/* Check if the password should always be requested */
	if (method->password_requested) {
		if (always_ask_selected (method->password_entry))
			widget_unset_error (GTK_WIDGET (method->password_entry));
		else {
			text = gtk_editable_get_text (GTK_EDITABLE (method->password_entry));
			if (!text || !strlen (text)) {
				widget_set_error (GTK_WIDGET (method->password_entry));
				if (ret) {
					g_set_error_literal (error, NMA_ERROR, NMA_ERROR_GENERIC,
					                     _("missing EAP password"));
					ret = FALSE;
				}
			} else
				widget_unset_error (GTK_WIDGET (method->password_entry));
		}
	}

	if (method->pkey_passphrase_requested) {
		text = gtk_editable_get_text (GTK_EDITABLE (method->pkey_passphrase_entry));
		if (!text || !strlen (text)) {
			widget_set_error (GTK_WIDGET (method->pkey_passphrase_entry));
			if (ret) {
				g_set_error_literal (error, NMA_ERROR, NMA_ERROR_GENERIC,
				                     _("missing EAP client Private Key passphrase"));
				ret = FALSE;
			}
		} else
			widget_unset_error (GTK_WIDGET (method->pkey_passphrase_entry));
	}

	return ret;
}

static void
add_to_size_group (EAPMethod *parent, GtkSizeGroup *group)
{
	EAPMethodSimple *method = (EAPMethodSimple *) parent;
	GtkWidget *widget;

	if (method->username_requested) {
		widget = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_simple_username_label"));
		g_assert (widget);
		gtk_size_group_add_widget (group, widget);
	}

	if (method->password_requested) {
		widget = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_simple_password_label"));
		g_assert (widget);
		gtk_size_group_add_widget (group, widget);
	}

	if (method->pkey_passphrase_requested) {
		widget = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_simple_pkey_passphrase_label"));
		g_assert (widget);
		gtk_size_group_add_widget (group, widget);
	}
}

typedef struct {
	const char *name;
	gboolean autheap_allowed;
} EapType;

/* Indexed by EAP_METHOD_SIMPLE_TYPE_* */
static const EapType eap_table[EAP_METHOD_SIMPLE_TYPE_LAST] = {
	[EAP_METHOD_SIMPLE_TYPE_PAP]             = { "pap",      FALSE },
	[EAP_METHOD_SIMPLE_TYPE_MSCHAP]          = { "mschap",   FALSE },
	[EAP_METHOD_SIMPLE_TYPE_MSCHAP_V2]       = { "mschapv2", TRUE  },
	[EAP_METHOD_SIMPLE_TYPE_PLAIN_MSCHAP_V2] = { "mschapv2", FALSE },
	[EAP_METHOD_SIMPLE_TYPE_MD5]             = { "md5",      TRUE  },
	[EAP_METHOD_SIMPLE_TYPE_PWD]             = { "pwd",      TRUE  },
	[EAP_METHOD_SIMPLE_TYPE_CHAP]            = { "chap",     FALSE },
	[EAP_METHOD_SIMPLE_TYPE_GTC]             = { "gtc",      TRUE  },
	[EAP_METHOD_SIMPLE_TYPE_UNKNOWN]         = { "unknown",  TRUE  },
};

static void
fill_connection (EAPMethod *parent, NMConnection *connection)
{
	EAPMethodSimple *method = (EAPMethodSimple *) parent;
	NMSetting8021x *s_8021x;
	gboolean not_saved = FALSE;
	NMSettingSecretFlags flags;
	const EapType *eap_type;

	s_8021x = nm_connection_get_setting_802_1x (connection);
	g_assert (s_8021x);

	if (!(method->flags & EAP_METHOD_SIMPLE_FLAG_SECRETS_ONLY)) {
		/* If this is the main EAP method, clear any existing methods because the
		 * user-selected one will replace it.
		 */
		if (parent->phase2 == FALSE)
			nm_setting_802_1x_clear_eap_methods (s_8021x);

		eap_type = &eap_table[method->type];
		if (parent->phase2) {
			/* If the outer EAP method (TLS, TTLS, PEAP, etc) allows inner/phase2
			 * EAP methods (which only TTLS allows) *and* the inner/phase2 method
			 * supports being an inner EAP method, then set PHASE2_AUTHEAP.
			 * Otherwise the inner/phase2 method goes into PHASE2_AUTH.
			 */
			if ((method->flags & EAP_METHOD_SIMPLE_FLAG_AUTHEAP_ALLOWED) && eap_type->autheap_allowed) {
				g_object_set (s_8021x, NM_SETTING_802_1X_PHASE2_AUTHEAP, eap_type->name, NULL);
				g_object_set (s_8021x, NM_SETTING_802_1X_PHASE2_AUTH, NULL, NULL);
			} else {
				g_object_set (s_8021x, NM_SETTING_802_1X_PHASE2_AUTH, eap_type->name, NULL);
				g_object_set (s_8021x, NM_SETTING_802_1X_PHASE2_AUTHEAP, NULL, NULL);
			}
		} else
			nm_setting_802_1x_add_eap_method (s_8021x, eap_type->name);
	}

	if (method->username_requested) {
		g_object_set (s_8021x, NM_SETTING_802_1X_IDENTITY,
		              gtk_editable_get_text (GTK_EDITABLE (method->username_entry)),
		              NULL);
	}

	if (method->password_requested) {
		/* Save the password always ask setting */
		not_saved = always_ask_selected (method->password_entry);
		flags = nma_utils_menu_to_secret_flags (GTK_WIDGET (method->password_entry));
		nm_setting_set_secret_flags (NM_SETTING (s_8021x), method->password_flags_name, flags, NULL);

		/* Fill the connection's password if we're in the applet so that it'll get
		 * back to NM.  From the editor though, since the connection isn't going
		 * back to NM in response to a GetSecrets() call, we don't save it if the
		 * user checked "Always Ask".
		 */
		if (!(method->flags & EAP_METHOD_SIMPLE_FLAG_IS_EDITOR) || not_saved == FALSE) {
			g_object_set (s_8021x, NM_SETTING_802_1X_PASSWORD,
			              gtk_editable_get_text (GTK_EDITABLE (method->password_entry)),
			              NULL);
		}

		/* Update secret flags and popup when editing the connection */
		if (!(method->flags & EAP_METHOD_SIMPLE_FLAG_SECRETS_ONLY)) {
			GtkWidget *passwd_entry = GTK_WIDGET (gtk_builder_get_object (parent->builder,
			                                                              "eap_simple_password_entry"));
			g_assert (passwd_entry);

			nma_utils_update_password_storage (passwd_entry, flags,
			                                   NM_SETTING (s_8021x), method->password_flags_name);
		}
	}

	if (method->pkey_passphrase_requested) {
		g_object_set (s_8021x, NM_SETTING_802_1X_PRIVATE_KEY_PASSWORD,
		              gtk_editable_get_text (GTK_EDITABLE (method->pkey_passphrase_entry)),
		              NULL);
	}
}

static void
update_secrets (EAPMethod *parent, NMConnection *connection)
{
	helper_fill_secret_entry (connection,
	                          parent->builder,
	                          "eap_simple_password_entry",
	                          NM_TYPE_SETTING_802_1X,
	                          (HelperSecretFunc) nm_setting_802_1x_get_password);
	helper_fill_secret_entry (connection,
	                          parent->builder,
	                          "eap_simple_pkey_passphrase_entry",
	                          NM_TYPE_SETTING_802_1X,
	                          (HelperSecretFunc) nm_setting_802_1x_get_private_key_password);
}

static gboolean
stuff_changed (EAPMethodSimple *method)
{
	wireless_security_changed_cb (NULL, method->ws_parent);
	method->idle_func_id = 0;
	return FALSE;
}

static void
password_storage_changed (GObject *entry,
                          GParamSpec *pspec,
                          EAPMethodSimple *method)
{
	gboolean always_ask;
	gboolean secrets_only = method->flags & EAP_METHOD_SIMPLE_FLAG_SECRETS_ONLY;

	always_ask = always_ask_selected (method->password_entry);

	if (always_ask && !secrets_only) {
		/* we always clear this button and do not restore it
		 * (because we want to hide the password). */
		gtk_toggle_button_set_active (method->show_password, FALSE);
	}

	gtk_widget_set_sensitive (GTK_WIDGET (method->show_password),
	                          !always_ask || secrets_only);

	if (!method->idle_func_id)
		method->idle_func_id = g_idle_add ((GSourceFunc) stuff_changed, method);
}

/* Set the UI fields for user, password, always_ask and show_password to the
 * values as provided by method->ws_parent. */
static void
set_userpass_ui (EAPMethodSimple *method)
{
	if (method->ws_parent->username) {
		gtk_editable_set_text (GTK_EDITABLE (method->username_entry),
		                       method->ws_parent->username);
	} else {
		gtk_editable_set_text (GTK_EDITABLE (method->username_entry), "");
	}

	if (method->ws_parent->password && !method->ws_parent->always_ask) {
		gtk_editable_set_text (GTK_EDITABLE (method->password_entry),
		                                     method->ws_parent->password);
	} else {
		gtk_editable_set_text (GTK_EDITABLE (method->password_entry), "");
	}

	gtk_toggle_button_set_active (method->show_password, method->ws_parent->show_password);
	password_storage_changed (NULL, NULL, method);
}

static void
widgets_realized (GtkWidget *widget, EAPMethodSimple *method)
{
	set_userpass_ui (method);
}

static void
widgets_unrealized (GtkWidget *widget, EAPMethodSimple *method)
{
	wireless_security_set_userpass (method->ws_parent,
	                                gtk_editable_get_text (GTK_EDITABLE (method->username_entry)),
	                                gtk_editable_get_text (GTK_EDITABLE (method->password_entry)),
	                                always_ask_selected (method->password_entry),
	                                gtk_toggle_button_get_active (method->show_password));
}

static void
destroy (EAPMethod *parent)
{
	EAPMethodSimple *method = (EAPMethodSimple *) parent;
	GtkWidget *widget;

	widget = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_simple_notebook"));
	g_assert (widget);
	g_signal_handlers_disconnect_by_data (widget, method);

	g_signal_handlers_disconnect_by_data (method->username_entry, method->ws_parent);
	g_signal_handlers_disconnect_by_data (method->password_entry, method->ws_parent);
	g_signal_handlers_disconnect_by_data (method->password_entry, method);
	g_signal_handlers_disconnect_by_data (method->show_password, method);
	g_signal_handlers_disconnect_by_data (method->pkey_passphrase_entry, method->ws_parent);
	g_signal_handlers_disconnect_by_data (method->show_pkey_passphrase, method);

	nm_clear_g_source (&method->idle_func_id);
}

static void
hide_row (GtkWidget **widgets, size_t num)
{
	while (num--)
		gtk_widget_hide (*widgets++);
}

EAPMethodSimple *
eap_method_simple_new (WirelessSecurity *ws_parent,
                       NMConnection *connection,
                       EAPMethodSimpleType type,
                       EAPMethodSimpleFlags flags,
                       const char *const*hints)
{
	EAPMethod *parent;
	EAPMethodSimple *method;
	GtkWidget *widget;
	NMSetting8021x *s_8021x = NULL;
	GtkWidget *widget_row[10];

	parent = eap_method_init (sizeof (EAPMethodSimple),
	                          validate,
	                          add_to_size_group,
	                          fill_connection,
	                          update_secrets,
	                          destroy,
	                          "/org/freedesktop/network-manager-applet/eap-method-simple.ui",
	                          "eap_simple_notebook",
	                          "eap_simple_username_entry",
	                          flags & EAP_METHOD_SIMPLE_FLAG_PHASE2);
	if (!parent)
		return NULL;

	method = (EAPMethodSimple *) parent;
	method->password_flags_name = NM_SETTING_802_1X_PASSWORD;
	method->ws_parent = ws_parent;
	method->flags = flags;
	method->type = type;
	g_assert (type < EAP_METHOD_SIMPLE_TYPE_LAST);
	g_assert (   type != EAP_METHOD_SIMPLE_TYPE_UNKNOWN
	          || hints);

	if (hints) {
		for (; *hints; hints++) {
			if (!strcmp (*hints, NM_SETTING_802_1X_IDENTITY))
				method->username_requested = TRUE;
			else if (!strcmp (*hints, NM_SETTING_802_1X_PASSWORD)) {
				method->password_requested = TRUE;
				method->password_flags_name = NM_SETTING_802_1X_PASSWORD;
			} else if (!strcmp (*hints, NM_SETTING_802_1X_PRIVATE_KEY_PASSWORD))
				method->pkey_passphrase_requested = TRUE;
		}
	} else {
		method->username_requested = TRUE;
		method->password_requested = TRUE;
	}

	widget = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_simple_notebook"));
	g_assert (widget);
	g_signal_connect (G_OBJECT (widget), "realize",
	                  (GCallback) widgets_realized,
	                  method);
	g_signal_connect (G_OBJECT (widget), "unrealize",
	                  (GCallback) widgets_unrealized,
	                  method);

	widget = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_simple_username_entry"));
	g_assert (widget);
	method->username_entry = GTK_ENTRY (widget);
	g_signal_connect (G_OBJECT (widget), "changed",
	                  (GCallback) wireless_security_changed_cb,
	                  ws_parent);

	if (   (method->flags & EAP_METHOD_SIMPLE_FLAG_SECRETS_ONLY)
	    && !method->username_requested)
		gtk_widget_set_sensitive (widget, FALSE);

	widget = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_simple_password_entry"));
	g_assert (widget);
	method->password_entry = GTK_ENTRY (widget);
	g_signal_connect (G_OBJECT (widget), "changed",
	                  (GCallback) wireless_security_changed_cb,
	                  ws_parent);

	/* Create password-storage popup menu for password entry under entry's secondary icon */
	if (connection)
		s_8021x = nm_connection_get_setting_802_1x (connection);
	nma_utils_setup_password_storage (widget, 0, (NMSetting *) s_8021x, method->password_flags_name,
	                                  FALSE, flags & EAP_METHOD_SIMPLE_FLAG_SECRETS_ONLY);

	g_signal_connect (method->password_entry, "notify::secondary-icon-name",
	                  G_CALLBACK (password_storage_changed),
	                  method);

	widget = GTK_WIDGET (gtk_builder_get_object (parent->builder, "show_checkbutton_eapsimple"));
	g_assert (widget);
	method->show_password = GTK_TOGGLE_BUTTON (widget);
	g_signal_connect (G_OBJECT (widget), "toggled",
	                  (GCallback) show_password_toggled_cb,
	                  method);

	widget = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_simple_pkey_passphrase_entry"));
	g_assert (widget);
	method->pkey_passphrase_entry = GTK_ENTRY (widget);
	g_signal_connect (G_OBJECT (widget), "changed",
	                  (GCallback) wireless_security_changed_cb,
	                  ws_parent);

	widget = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_simple_show_pkey_passphrase_checkbutton"));
	g_assert (widget);
	method->show_pkey_passphrase = GTK_TOGGLE_BUTTON (widget);
	g_signal_connect (G_OBJECT (widget), "toggled",
	                  (GCallback) show_pkey_passphrase_toggled_cb,
	                  method);

	widget_row[0] = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_simple_username_label"));
	widget_row[1] = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_simple_username_entry"));
	if (!method->username_requested)
		hide_row (widget_row, 2);

	widget_row[0] = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_simple_password_label"));
	widget_row[1] = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_simple_password_entry"));
	widget_row[2] = GTK_WIDGET (gtk_builder_get_object (parent->builder, "show_checkbutton_eapsimple"));
	if (!method->password_requested)
		hide_row (widget_row, 3);

	widget_row[0] = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_simple_pkey_passphrase_label"));
	widget_row[1] = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_simple_pkey_passphrase_entry"));
	widget_row[2] = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_simple_show_pkey_passphrase_checkbutton"));
	if (!method->pkey_passphrase_requested)
		hide_row (widget_row, 3);

	/* Initialize the UI fields with the security settings from method->ws_parent.
	 * This will be done again when the widget gets realized. It must be done here as well,
	 * because the outer dialog will ask to 'validate' the connection before the security tab
	 * is shown/realized (to enable the 'Apply' button).
	 * As 'validate' accesses the contents of the UI fields, they must be initialized now, even
	 * if the widgets are not yet visible. */
	set_userpass_ui (method);

	return method;
}
