// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Copyright 2020 Red Hat, Inc.
 */

#include "nm-default.h"

#include <string.h>

#include "page-wireguard.h"
#include "nm-connection-editor.h"
#include "nma-ui-utils.h"

G_DEFINE_TYPE (CEPageWireGuard, ce_page_wireguard, CE_TYPE_PAGE)

#define CE_PAGE_WIREGUARD_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), CE_TYPE_PAGE_WIREGUARD, CEPageWireGuardPrivate))

typedef struct {
	NMWireGuardPeer *peer;
	GtkInfoBar *info_bar;
	GtkLabel *label_info;
	GtkButton *button_apply;
	GtkBuilder *builder;
	GtkEntry *entry_public_key;
	GtkEntry *entry_allowed_ips;
	GtkEntry *entry_endpoint;
	GtkEntry *entry_psk;
	GtkSpinButton *spin_persistent_keepalive;
	GtkToggleButton *toggle_show_psk;
} PeerDialogData;

typedef struct {
	NMSettingWireGuard *setting;

	NMWireGuardPeer *dialog_peer;
	int dialog_peer_index;

	GtkEntry *entry_ifname;
	GtkEntry *entry_pk;
	GtkSpinButton *spin_mtu;
	GtkSpinButton *spin_fwmark;
	GtkSpinButton *spin_listen_port;
	GtkToggleButton *toggle_peer_routes;
	GtkToggleButton *toggle_show_pk;
	GtkButton *button_add;
	GtkButton *button_delete;

	GtkTreeView *tree;
	GtkTreeStore *store;
} CEPageWireGuardPrivate;

enum {
	COL_PUBLIC_KEY,
	COL_ALLOWED_IPS,
	N_COLUMNS,
};

static void
peer_dialog_data_destroy (PeerDialogData *data)
{
	g_object_unref (data->builder);
	nm_wireguard_peer_unref (data->peer);
	g_free (data);
}

static char *
format_allowed_ips (NMWireGuardPeer *peer)
{
	guint i, len;
	GString *string = NULL;

	len = nm_wireguard_peer_get_allowed_ips_len (peer);
	for (i = 0; i < len; i++) {
		if (!string)
			string = g_string_new ("");
		else
			g_string_append_c (string, ',');
		g_string_append (string, nm_wireguard_peer_get_allowed_ip (peer, i, NULL));
	}

	return string ? g_string_free (string, FALSE) : NULL;
}

static void
peer_dialog_update_ui (GtkWidget *dialog)
{
	PeerDialogData *data;
	gs_free char *allowed_ips = NULL;

	data = g_object_get_data (G_OBJECT (dialog), "data");
	g_return_if_fail (data && data->peer);

	allowed_ips = format_allowed_ips (data->peer);

	gtk_entry_set_text (data->entry_public_key, nm_wireguard_peer_get_public_key (data->peer) ?: "");
	gtk_entry_set_text (data->entry_allowed_ips, allowed_ips ?: "");
	gtk_entry_set_text (data->entry_endpoint, nm_wireguard_peer_get_endpoint (data->peer) ?: "");
	gtk_spin_button_set_value (data->spin_persistent_keepalive, nm_wireguard_peer_get_persistent_keepalive (data->peer));
	gtk_entry_set_text (data->entry_psk, nm_wireguard_peer_get_preshared_key (data->peer) ?: "");

	nma_utils_update_password_storage (GTK_WIDGET (data->entry_psk),
	                                   nm_wireguard_peer_get_preshared_key_flags (data->peer),
	                                   NULL,
	                                   NULL);
}

static void
peer_dialog_update_peer (GtkWidget *dialog)
{
	PeerDialogData *data;
	const char *pk;
	const char *allowed_ips;
	const char *endpoint;
	const char *psk;
	char **strv;
	guint i;
	int keepalive;
	NMSettingSecretFlags secret_flags;

	data = g_object_get_data (G_OBJECT (dialog), "data");
	g_return_if_fail (data && data->peer);

	pk = gtk_entry_get_text (data->entry_public_key);
	nm_wireguard_peer_set_public_key (data->peer, pk && pk[0] ? pk : NULL, TRUE);

	nm_wireguard_peer_clear_allowed_ips (data->peer);
	allowed_ips = gtk_entry_get_text (data->entry_allowed_ips);
	strv = g_strsplit (allowed_ips, ",", -1);
	for (i = 0; strv && strv[i]; i++)
		nm_wireguard_peer_append_allowed_ip (data->peer, g_strstrip (strv[i]), TRUE);
	g_strfreev (strv);

	endpoint = gtk_entry_get_text (data->entry_endpoint);
	nm_wireguard_peer_set_endpoint (data->peer, endpoint && endpoint[0] ? endpoint : NULL, TRUE);

	keepalive = gtk_spin_button_get_value_as_int (data->spin_persistent_keepalive);
	nm_wireguard_peer_set_persistent_keepalive (data->peer, keepalive);

	psk = gtk_entry_get_text (data->entry_psk);
	nm_wireguard_peer_set_preshared_key (data->peer, psk && psk[0] ? psk : NULL, TRUE);

	secret_flags = nma_utils_menu_to_secret_flags ((GtkWidget *) data->entry_psk);
	nm_wireguard_peer_set_preshared_key_flags (data->peer, secret_flags);
}

static void
peer_dialog_apply_clicked (GtkWidget *dialog)
{
	PeerDialogData *data;
	gs_free_error GError *error = NULL;
	gs_free char *reason = NULL;

	data = g_object_get_data (G_OBJECT (dialog), "data");

	if (!nm_wireguard_peer_is_valid (data->peer, TRUE, TRUE, &error)) {
		reason = g_strdup_printf ("Error: %s", error->message);
		gtk_label_set_text (data->label_info, reason);
		gtk_widget_set_visible (GTK_WIDGET (data->info_bar), TRUE);
	} else {
		gtk_label_set_text (data->label_info, "");
		gtk_widget_set_visible (GTK_WIDGET (data->info_bar), FALSE);
		gtk_dialog_response (GTK_DIALOG (dialog), GTK_RESPONSE_APPLY);
	}
}

static void
peer_dialog_show_psk (GtkDialog *dialog)
{
	PeerDialogData *data;

	data = g_object_get_data (G_OBJECT (dialog), "data");
	gtk_entry_set_visibility (data->entry_psk,
	                          gtk_toggle_button_get_active (data->toggle_show_psk));
}

static GtkWidget *
peer_dialog_create (GtkWidget *toplevel, NMWireGuardPeer *peer)
{
	GtkWidget *dialog;
	gs_free_error GError *error = NULL;
	PeerDialogData *data;
	GtkBuilder *builder;

	builder = gtk_builder_new ();

	if (!gtk_builder_add_from_resource (builder,
	                                    "/org/gnome/nm_connection_editor/ce-page-wireguard.ui",
	                                    &error)) {
		g_warning ("Couldn't load builder resource: %s", error->message);
		g_error_free (error);
		return NULL;
	}

	dialog = GTK_WIDGET (gtk_builder_get_object (builder, "PeerDialog"));

	data = g_new0 (PeerDialogData, 1);
	data->peer = nm_wireguard_peer_ref (peer);
	data->builder = builder;
	data->button_apply = GTK_BUTTON (gtk_builder_get_object (builder, "button_apply"));
	data->entry_public_key = GTK_ENTRY (gtk_builder_get_object (builder, "entry_public_key"));
	data->entry_allowed_ips = GTK_ENTRY (gtk_builder_get_object (builder, "entry_allowed_ips"));
	data->entry_endpoint = GTK_ENTRY (gtk_builder_get_object (builder, "entry_endpoint"));
	data->entry_psk = GTK_ENTRY (gtk_builder_get_object (builder, "entry_psk"));
	data->spin_persistent_keepalive = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spin_persistent_keepalive"));
	data->info_bar = GTK_INFO_BAR (gtk_builder_get_object (builder, "info_bar"));
	data->label_info = GTK_LABEL (gtk_builder_get_object (builder, "label_info"));
	data->toggle_show_psk = GTK_TOGGLE_BUTTON (gtk_builder_get_object (builder, "toggle_show_psk"));

	g_object_set_data_full (G_OBJECT (dialog), "data",
	                        data,
	                        (GDestroyNotify) peer_dialog_data_destroy);

	nma_utils_setup_password_storage ((GtkWidget *) data->entry_psk, 0,
	                                  NULL, NULL, TRUE, FALSE);
	ce_spin_off_val (data->spin_persistent_keepalive, 0);

	gtk_entry_set_visibility (data->entry_psk, FALSE);

	peer_dialog_update_ui (dialog);

	g_signal_connect_swapped (data->button_apply, "clicked", G_CALLBACK (peer_dialog_apply_clicked), dialog);
	g_signal_connect_swapped (data->entry_public_key, "changed", G_CALLBACK (peer_dialog_update_peer), dialog);
	g_signal_connect_swapped (data->entry_allowed_ips, "changed", G_CALLBACK (peer_dialog_update_peer), dialog);
	g_signal_connect_swapped (data->entry_endpoint, "changed", G_CALLBACK (peer_dialog_update_peer), dialog);
	g_signal_connect_swapped (data->entry_psk, "changed", G_CALLBACK (peer_dialog_update_peer), dialog);
	g_signal_connect_swapped (data->toggle_show_psk, "toggled", G_CALLBACK (peer_dialog_show_psk), dialog);

	gtk_label_set_text (data->label_info, "");
	gtk_widget_set_visible (GTK_WIDGET (data->info_bar), FALSE);

	gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);
	gtk_window_set_transient_for (GTK_WINDOW (dialog), GTK_WINDOW (toplevel));

	return dialog;
}

static void
wireguard_private_init (CEPageWireGuard *self)
{
	CEPageWireGuardPrivate *priv = CE_PAGE_WIREGUARD_GET_PRIVATE (self);
	GtkBuilder *builder;
	GtkTreeViewColumn *column;

	builder = CE_PAGE (self)->builder;

	priv->entry_ifname = GTK_ENTRY (gtk_builder_get_object (builder, "entry_ifname"));
	priv->entry_pk = GTK_ENTRY (gtk_builder_get_object (builder, "entry_private_key"));
	priv->spin_mtu = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spin_mtu"));
	priv->spin_fwmark = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spin_fwmark"));
	priv->spin_listen_port = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spin_listen_port"));
	priv->toggle_peer_routes = GTK_TOGGLE_BUTTON (gtk_builder_get_object (builder, "toggle_peer_routes"));
	priv->toggle_show_pk = GTK_TOGGLE_BUTTON (gtk_builder_get_object (builder, "toggle_show_private_key"));
	priv->tree = GTK_TREE_VIEW (gtk_builder_get_object (builder, "tree_peers"));
	priv->button_add = GTK_BUTTON (gtk_builder_get_object (builder, "button_add"));
	priv->button_delete = GTK_BUTTON (gtk_builder_get_object (builder, "button_delete"));

	gtk_entry_set_visibility (priv->entry_pk, FALSE);

	priv->store = gtk_tree_store_new (3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_POINTER);
	column = gtk_tree_view_column_new_with_attributes (_("Public key"),
	                                                   gtk_cell_renderer_text_new (),
	                                                   "text", COL_PUBLIC_KEY,
	                                                   NULL);
	gtk_tree_view_column_set_resizable (column, TRUE);
	gtk_tree_view_append_column (priv->tree, column);

	column = gtk_tree_view_column_new_with_attributes (_("Allowed IPs"),
	                                                   gtk_cell_renderer_text_new (),
	                                                   "text", COL_ALLOWED_IPS,
	                                                   NULL);
	gtk_tree_view_column_set_resizable (column, TRUE);
	gtk_tree_view_append_column (priv->tree, column);

	gtk_tree_view_set_model (priv->tree, GTK_TREE_MODEL (priv->store));
}

static void
update_peers_table (CEPageWireGuard *self)
{
	CEPageWireGuardPrivate *priv = CE_PAGE_WIREGUARD_GET_PRIVATE (self);
	NMSettingWireGuard *setting = priv->setting;
	guint i, num;

	gtk_tree_store_clear (priv->store);

	num = nm_setting_wireguard_get_peers_len (setting);
	for (i = 0; i < num; i++) {
		NMWireGuardPeer *peer;
		GtkTreeIter iter;
		gs_free char *ips = NULL;

		peer = nm_setting_wireguard_get_peer (setting, i);
		ips = format_allowed_ips (peer);
		gtk_tree_store_append (priv->store, &iter, NULL);

		gtk_tree_store_set (priv->store, &iter,
		                    COL_PUBLIC_KEY, nm_wireguard_peer_get_public_key (peer),
		                    COL_ALLOWED_IPS, ips,
		                    -1);
	}
}

static int
get_selected_index (CEPageWireGuard *self)
{
	CEPageWireGuardPrivate *priv = CE_PAGE_WIREGUARD_GET_PRIVATE (self);
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GList *list;
	int *indices;
	int ret = -1;

	selection = gtk_tree_view_get_selection (priv->tree);
	nm_assert (selection);

	list = gtk_tree_selection_get_selected_rows (selection, &model);
	if (!list)
		goto done;

	indices = gtk_tree_path_get_indices ((GtkTreePath *) list->data);
	if (!indices)
		goto done;

	ret = indices[0];
done:
	g_list_free_full (list, (GDestroyNotify) gtk_tree_path_free);
	return ret;
}

static void
tree_selection_changed (CEPageWireGuard *self)
{
	CEPageWireGuardPrivate *priv = CE_PAGE_WIREGUARD_GET_PRIVATE (self);
	int index;

	index = get_selected_index (self);
	gtk_widget_set_sensitive (GTK_WIDGET (priv->button_delete), index >= 0);
}

static void
populate_ui (CEPageWireGuard *self)
{
	CEPageWireGuardPrivate *priv = CE_PAGE_WIREGUARD_GET_PRIVATE (self);
	NMSettingWireGuard *setting = priv->setting;
	NMConnection *connection;
	const char *str;

	connection = CE_PAGE (self)->connection;
	str = nm_connection_get_interface_name (connection);
	if (str)
		gtk_entry_set_text (priv->entry_ifname, str);

	gtk_entry_set_text (priv->entry_pk, nm_setting_wireguard_get_private_key (setting) ?: "");
	nma_utils_setup_password_storage ((GtkWidget *) priv->entry_pk, 0,
	                                  (NMSetting *) priv->setting,
	                                  NM_SETTING_WIREGUARD_PRIVATE_KEY,
	                                  FALSE, FALSE);

	ce_spin_automatic_val (priv->spin_mtu, 0);
	ce_spin_automatic_val (priv->spin_listen_port, 0);
	ce_spin_off_val (priv->spin_fwmark, 0);

	gtk_spin_button_set_value (priv->spin_mtu, nm_setting_wireguard_get_mtu (setting));
	gtk_spin_button_set_value (priv->spin_fwmark, nm_setting_wireguard_get_fwmark (setting));
	gtk_spin_button_set_value (priv->spin_listen_port, nm_setting_wireguard_get_listen_port (setting));

	gtk_toggle_button_set_active (priv->toggle_peer_routes,
	                              nm_setting_wireguard_get_peer_routes (setting));

	update_peers_table (self);
	tree_selection_changed (self);
}

static void
stuff_changed (GtkEditable *editable, gpointer user_data)
{
	ce_page_changed (CE_PAGE (user_data));
}

static void
peer_dialog_response_cb (GtkWidget *dialog, gint response, gpointer user_data)
{
	CEPageWireGuard *self = CE_PAGE_WIREGUARD (user_data);
	CEPageWireGuardPrivate *priv = CE_PAGE_WIREGUARD_GET_PRIVATE (self);

	if (response == GTK_RESPONSE_APPLY) {
		peer_dialog_update_peer (dialog);
		if (priv->dialog_peer_index >= 0) {
			nm_setting_wireguard_set_peer (priv->setting,
			                               priv->dialog_peer,
			                               priv->dialog_peer_index);
		} else {
			nm_setting_wireguard_append_peer (priv->setting,
			                                  priv->dialog_peer);
		}
		update_peers_table (self);
	}

	nm_wireguard_peer_unref (priv->dialog_peer);
	priv->dialog_peer = NULL;
	priv->dialog_peer_index = -1;

	gtk_widget_hide (dialog);
	gtk_widget_destroy (dialog);
}

static void
add_delete_clicked (GtkButton *button, CEPageWireGuard *self)
{
	CEPageWireGuardPrivate *priv = CE_PAGE_WIREGUARD_GET_PRIVATE (self);
	GtkWidget *dialog;
	int index;

	g_return_if_fail (NM_IN_SET (button, priv->button_add, priv->button_delete));

	if (button == priv->button_add) {
		priv->dialog_peer = nm_wireguard_peer_new ();
		priv->dialog_peer_index = -1;
		dialog = peer_dialog_create (gtk_widget_get_toplevel (CE_PAGE (self)->page),
		                             priv->dialog_peer);
		if (!dialog)
			return;
		g_signal_connect (G_OBJECT (dialog), "response", G_CALLBACK (peer_dialog_response_cb), self);
		gtk_widget_show (dialog);
	} else {
		index = get_selected_index (self);
		if (index >= 0) {
			nm_setting_wireguard_remove_peer (priv->setting, (guint) index);
			update_peers_table (self);
		}
	}
}

static void
row_activated (GtkTreeView       *tree_view,
               GtkTreePath       *path,
               GtkTreeViewColumn *column,
               CEPageWireGuard   *self)
{
	CEPageWireGuardPrivate *priv = CE_PAGE_WIREGUARD_GET_PRIVATE (self);
	NMWireGuardPeer *peer;
	GtkWidget *dialog;
	int index;

	index = get_selected_index (self);
	if (index < 0)
		return;

	peer = nm_setting_wireguard_get_peer (priv->setting, index);
	priv->dialog_peer = nm_wireguard_peer_new_clone (peer, TRUE);
	priv->dialog_peer_index = index;

	dialog = peer_dialog_create (gtk_widget_get_toplevel (CE_PAGE (self)->page),
	                             priv->dialog_peer);
	if (!dialog)
		return;

	g_signal_connect (G_OBJECT (dialog), "response", G_CALLBACK (peer_dialog_response_cb), self);
	gtk_widget_show (dialog);
}

static void
show_private_key (GtkToggleButton *button, gpointer user_data)
{
	CEPageWireGuardPrivate *priv = CE_PAGE_WIREGUARD_GET_PRIVATE (user_data);

	gtk_entry_set_visibility (priv->entry_pk, gtk_toggle_button_get_active (button));
}

static void
finish_setup (CEPageWireGuard *self, gpointer user_data)
{
	CEPageWireGuardPrivate *priv = CE_PAGE_WIREGUARD_GET_PRIVATE (self);
	GtkTreeSelection *selection;

	selection = gtk_tree_view_get_selection (priv->tree);
	populate_ui (self);

	g_signal_connect (priv->entry_ifname,      "changed",       G_CALLBACK (stuff_changed), self);
	g_signal_connect (priv->entry_pk,          "changed",       G_CALLBACK (stuff_changed), self);
	g_signal_connect (priv->spin_mtu,          "value-changed", G_CALLBACK (stuff_changed), self);
	g_signal_connect (priv->spin_listen_port,  "value-changed", G_CALLBACK (stuff_changed), self);
	g_signal_connect (priv->button_add,        "clicked",       G_CALLBACK (add_delete_clicked), self);
	g_signal_connect (priv->button_delete,     "clicked",       G_CALLBACK (add_delete_clicked), self);
	g_signal_connect (priv->tree,              "row-activated", G_CALLBACK (row_activated), self);
	g_signal_connect (priv->toggle_show_pk,    "toggled",       G_CALLBACK (show_private_key), self);

	g_signal_connect_swapped (selection,       "changed",       G_CALLBACK (tree_selection_changed), self);
}

CEPage *
ce_page_wireguard_new (NMConnectionEditor *editor,
                       NMConnection *connection,
                       GtkWindow *parent_window,
                       NMClient *client,
                       const char **out_secrets_setting_name,
                       GError **error)
{
	CEPageWireGuard *self;
	CEPageWireGuardPrivate *priv;

	self = CE_PAGE_WIREGUARD (ce_page_new (CE_TYPE_PAGE_WIREGUARD,
	                                       editor,
	                                       connection,
	                                       parent_window,
	                                       client,
	                                       "/org/gnome/nm_connection_editor/ce-page-wireguard.ui",
	                                       "WireGuardPage",
	                                      _("WireGuard")));
	if (!self) {
		g_set_error_literal (error, NMA_ERROR, NMA_ERROR_GENERIC, _("Could not load WireGuard user interface."));
		return NULL;
	}

	wireguard_private_init (self);
	priv = CE_PAGE_WIREGUARD_GET_PRIVATE (self);

	priv->setting = (NMSettingWireGuard *) nm_connection_get_setting (connection, NM_TYPE_SETTING_WIREGUARD);
	if (!priv->setting) {
		priv->setting = NM_SETTING_WIREGUARD (nm_setting_wireguard_new ());
		nm_connection_add_setting (connection, NM_SETTING (priv->setting));
	}

	g_signal_connect (self, CE_PAGE_INITIALIZED, G_CALLBACK (finish_setup), NULL);

	*out_secrets_setting_name = NM_SETTING_WIREGUARD_SETTING_NAME;

	return CE_PAGE (self);
}

static void
ui_to_setting (CEPageWireGuard *self)
{
	CEPageWireGuardPrivate *priv = CE_PAGE_WIREGUARD_GET_PRIVATE (self);
	NMSettingConnection *s_con;
	guint32 mtu;
	guint32 fwmark;
	guint16 listen_port;
	const char *private_key;
	const char *ifname;
	NMSettingSecretFlags secret_flags;
	gboolean peer_routes;

	s_con = nm_connection_get_setting_connection (CE_PAGE (self)->connection);
	g_return_if_fail (s_con != NULL);

	ifname = gtk_entry_get_text (priv->entry_ifname);
	if (ifname && ifname[0] == '\0')
		ifname = NULL;
	g_object_set (s_con,
	              NM_SETTING_CONNECTION_INTERFACE_NAME,
	              ifname,
	              NULL);

	private_key = gtk_entry_get_text (priv->entry_pk);
	if (private_key && private_key[0] == '\0')
		private_key = NULL;
	mtu = gtk_spin_button_get_value_as_int (priv->spin_mtu);
	fwmark = gtk_spin_button_get_value_as_int (priv->spin_fwmark);
	listen_port = gtk_spin_button_get_value_as_int (priv->spin_listen_port);
	peer_routes = gtk_toggle_button_get_active (priv->toggle_peer_routes);

	g_object_set (priv->setting,
	              NM_SETTING_WIREGUARD_PRIVATE_KEY, private_key,
	              NM_SETTING_WIREGUARD_LISTEN_PORT, listen_port,
	              NM_SETTING_WIREGUARD_FWMARK, fwmark,
	              NM_SETTING_WIREGUARD_MTU, mtu,
	              NM_SETTING_WIREGUARD_PEER_ROUTES, peer_routes,
	              NULL);

	/* Save private key flags to the connection */
	secret_flags = nma_utils_menu_to_secret_flags ((GtkWidget *) priv->entry_pk);
	nm_setting_set_secret_flags (NM_SETTING (priv->setting),
	                             NM_SETTING_WIREGUARD_PRIVATE_KEY,
	                             secret_flags, NULL);

	/* Update secret flags and popup when editing the connection */
	nma_utils_update_password_storage ((GtkWidget *) priv->entry_pk,
	                                   secret_flags,
	                                   NM_SETTING (priv->setting),
	                                   NM_SETTING_WIREGUARD_PRIVATE_KEY);
}

static gboolean
ce_page_validate_v (CEPage *page, NMConnection *connection, GError **error)
{
	CEPageWireGuard *self = CE_PAGE_WIREGUARD (page);
	CEPageWireGuardPrivate *priv = CE_PAGE_WIREGUARD_GET_PRIVATE (self);

	ui_to_setting (self);

	return    nm_setting_verify (NM_SETTING (priv->setting), connection, error)
	       && nm_setting_verify_secrets (NM_SETTING (priv->setting), connection, error);
}

static void
ce_page_wireguard_init (CEPageWireGuard *self)
{
}

static void
ce_page_wireguard_class_init (CEPageWireGuardClass *wireguard_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (wireguard_class);
	CEPageClass *parent_class = CE_PAGE_CLASS (wireguard_class);

	g_type_class_add_private (object_class, sizeof (CEPageWireGuardPrivate));

	parent_class->ce_page_validate_v = ce_page_validate_v;
}

void
wireguard_connection_new (FUNC_TAG_PAGE_NEW_CONNECTION_IMPL,
                          GtkWindow *parent,
                          const char *detail,
                          gpointer detail_data,
                          NMConnection *connection,
                          NMClient *client,
                          PageNewConnectionResultFunc result_func,
                          gpointer user_data)
{
	gs_unref_object NMConnection *connection_tmp = NULL;
	NMSettingIPConfig *s_ip;

	connection = _ensure_connection_other (connection, &connection_tmp);
	ce_page_complete_connection (connection,
	                             _("WireGuard connection %d"),
	                             NM_SETTING_WIREGUARD_SETTING_NAME,
	                             FALSE,
	                             client);
	nm_connection_add_setting (connection, nm_setting_wireguard_new ());

	s_ip = (NMSettingIPConfig *) nm_setting_ip4_config_new ();
	g_object_set (s_ip, NM_SETTING_IP_CONFIG_METHOD, NM_SETTING_IP4_CONFIG_METHOD_DISABLED, NULL);
	nm_connection_add_setting (connection, (NMSetting *) s_ip);

	s_ip = (NMSettingIPConfig *) nm_setting_ip6_config_new ();
	g_object_set (s_ip, NM_SETTING_IP_CONFIG_METHOD, NM_SETTING_IP6_CONFIG_METHOD_IGNORE, NULL);
	nm_connection_add_setting (connection, (NMSetting *) s_ip);

	(*result_func) (FUNC_TAG_PAGE_NEW_CONNECTION_RESULT_CALL, connection, FALSE, NULL, user_data);
}
