// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Dan Williams <dcbw@redhat.com>
 * Lubomir Rintel <lkundrak@v3.sk>
 *
 * (C) Copyright 2008 - 2018 Red Hat, Inc.
 */

#include "nm-default.h"
#include "nma-private.h"

#include <stdlib.h>

#if GTK_CHECK_VERSION(3,90,0)
#include <gdk/x11/gdkx.h>
#else
#include <gdk/gdkx.h>
#endif

#include <NetworkManager.h>
#include <nm-setting-gsm.h>
#include <nm-setting-cdma.h>
#include <nm-client.h>
#include <nm-device-modem.h>

#include "nma-mobile-wizard.h"
#include "nma-mobile-providers.h"
#include "utils.h"

#define DEVICE_TAG "device"
#define TYPE_TAG "setting-type"

#define INTRO_PAGE_IDX      0
#define COUNTRY_PAGE_IDX    1
#define PROVIDERS_PAGE_IDX  2
#define PLAN_PAGE_IDX       3
#define CONFIRM_PAGE_IDX    4

static NMACountryInfo *get_selected_country (NMAMobileWizard *self);
static NMAMobileProvider *get_selected_provider (NMAMobileWizard *self);
static NMAMobileFamily get_provider_unlisted_type (NMAMobileWizard *self);
static NMAMobileAccessMethod *get_selected_method (NMAMobileWizard *self, gboolean *manual);

#include "nm-default.h"

struct _NMAMobileWizard {
        GtkAssistant parent;
};

struct _NMAMobileWizardClass {
        GtkAssistantClass parent;
};

typedef struct {
	NMAMobileWizardCallback callback;
	gpointer user_data;
	NMAMobileProvidersDatabase *mobile_providers_database;
	NMAMobileFamily family;
	gboolean initial_family;
	gboolean will_connect_after;

	/* Intro page */
	GtkLabel *dev_combo_label;
	GtkComboBox *dev_combo;
	GtkLabel *provider_name_label;
	GtkLabel *plan_name_label;
	GtkLabel *apn_label;
	GtkTreeStore *dev_store;
	char *dev_desc;
	NMClient *client;

	/* Country page */
	NMACountryInfo *country;
	GtkWidget *country_page;
	GtkTreeView *country_view;
	GtkTreeStore *country_store;
	GtkTreeModelSort *country_sort;
	guint32 country_focus_id;

	/* Providers page */
	GtkWidget *providers_page;
	GtkTreeView *providers_view;
	GtkTreeStore *providers_store;
	GtkTreeModel *providers_sort;
	guint32 providers_focus_id;
	GtkToggleButton *providers_view_radio;

	GtkToggleButton *provider_unlisted_radio;
	GtkComboBox *provider_unlisted_type_combo;

	gboolean provider_only_cdma;

	/* Plan page */
	GtkWidget *plan_page;
	GtkComboBox *plan_combo;
	GtkTreeStore *plan_store;
	guint32 plan_focus_id;

	GtkEditable *plan_apn_entry;

	/* Confirm page */
	GtkWidget *confirm_page;
	GtkLabel *confirm_provider;
	GtkLabel *confirm_plan;
	GtkLabel *confirm_apn;
	GtkLabel *confirm_plan_label;
	GtkLabel *confirm_device;
	GtkLabel *confirm_device_label;
	GtkWidget *confirm_connect_after_label;
} NMAMobileWizardPrivate;

#define NMA_MOBILE_WIZARD_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
                                          NMA_TYPE_MOBILE_WIZARD, \
                                          NMAMobileWizardPrivate))

G_DEFINE_TYPE_WITH_CODE (NMAMobileWizard, nma_mobile_wizard, GTK_TYPE_ASSISTANT,
                         G_ADD_PRIVATE (NMAMobileWizard))

static void
assistant_closed (GtkButton *button, gpointer user_data)
{
	NMAMobileWizard *self = NMA_MOBILE_WIZARD (user_data);
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	NMAMobileProvider *provider;
	NMAMobileAccessMethod *method;
	NMAMobileWizardAccessMethod *wiz_method;
	NMAMobileFamily family = priv->family;

	wiz_method = g_malloc0 (sizeof (NMAMobileWizardAccessMethod));

	provider = get_selected_provider (self);
	if (!provider) {
		if (family == NMA_MOBILE_FAMILY_UNKNOWN)
			family = get_provider_unlisted_type (self);

		switch (family) {
		case NMA_MOBILE_FAMILY_3GPP:
			wiz_method->provider_name = g_strdup (_("GSM"));
			break;
		case NMA_MOBILE_FAMILY_CDMA:
			wiz_method->provider_name = g_strdup (_("CDMA"));
			break;
		case NMA_MOBILE_FAMILY_UNKNOWN:
			g_return_if_reached ();
			break;
		}
	} else {
		gboolean manual = FALSE;

		wiz_method->provider_name = g_strdup (nma_mobile_provider_get_name (provider));
		method = get_selected_method (self, &manual);
		if (method) {
			family = nma_mobile_access_method_get_family (method);
			wiz_method->plan_name = g_strdup (nma_mobile_access_method_get_name (method));
			wiz_method->username = g_strdup (nma_mobile_access_method_get_username (method));
			wiz_method->password = g_strdup (nma_mobile_access_method_get_password (method));
			if (family == NMA_MOBILE_FAMILY_3GPP)
				wiz_method->gsm_apn = g_strdup (nma_mobile_access_method_get_3gpp_apn (method));
		} else {
			if (priv->provider_only_cdma) {
				GSList *methods;

				family = NMA_MOBILE_FAMILY_CDMA;

				methods = nma_mobile_provider_get_methods (provider);
				/* Take username and password from the first (only) method for CDMA only provider */
				if (methods) {
					method = methods->data;
					wiz_method->username = g_strdup (nma_mobile_access_method_get_username (method));
					wiz_method->password = g_strdup (nma_mobile_access_method_get_password (method));
				}
			} else {
				family = NMA_MOBILE_FAMILY_3GPP;
				wiz_method->gsm_apn = g_strdup (gtk_editable_get_text (priv->plan_apn_entry));
			}
		}
	}

	switch (family) {
	case NMA_MOBILE_FAMILY_3GPP:
		wiz_method->devtype = NM_DEVICE_MODEM_CAPABILITY_GSM_UMTS;
		break;
	case NMA_MOBILE_FAMILY_CDMA:
		wiz_method->devtype = NM_DEVICE_MODEM_CAPABILITY_CDMA_EVDO;
		break;
	default:
		g_return_if_reached ();
		break;
	}

	(*(priv->callback)) (self, FALSE, wiz_method, priv->user_data);

	if (provider)
		nma_mobile_provider_unref (provider);
	g_free (wiz_method->provider_name);
	g_free (wiz_method->plan_name);
	g_free (wiz_method->username);
	g_free (wiz_method->password);
	g_free (wiz_method->gsm_apn);
	g_free (wiz_method);
}

static void
assistant_cancel (GtkButton *button, gpointer user_data)
{
	NMAMobileWizard *self = user_data;
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	(*(priv->callback)) (self, TRUE, NULL, priv->user_data);
}

/**********************************************************/
/* Confirm page */
/**********************************************************/

static void
confirm_setup (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	if (priv->will_connect_after)
		gtk_widget_show (priv->confirm_connect_after_label);
}

static void
confirm_prepare (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	NMAMobileProvider *provider = NULL;
	NMAMobileAccessMethod *method = NULL;
	const char *apn = NULL;
	NMACountryInfo *country_info;
	gboolean manual = FALSE;
	GString *str;

	provider = get_selected_provider (self);
	if (provider)
		method = get_selected_method (self, &manual);

	/* Provider */
	str = g_string_new (NULL);
	if (provider) {
		g_string_append (str, nma_mobile_provider_get_name (provider));
		nma_mobile_provider_unref (provider);
	} else {
		g_string_append (str, _("Unlisted"));
	}

	country_info = get_selected_country (self);
	if (nma_country_info_get_country_code (country_info))
		g_string_append_printf (str, ", %s", nma_country_info_get_country_name (country_info));
	nma_country_info_unref (country_info);

	gtk_label_set_text (priv->confirm_provider, str->str);
	gtk_widget_show (GTK_WIDGET (priv->confirm_provider));
	g_string_free (str, TRUE);

	if (priv->dev_desc) {
		gtk_label_set_text (priv->confirm_device, priv->dev_desc);
		gtk_widget_show (GTK_WIDGET (priv->confirm_device_label));
		gtk_widget_show (GTK_WIDGET (priv->confirm_device));
	} else {
		gtk_widget_hide (GTK_WIDGET (priv->confirm_device_label));
		gtk_widget_hide (GTK_WIDGET (priv->confirm_device));
	}

	if (priv->provider_only_cdma) {
		gtk_widget_hide (GTK_WIDGET (priv->confirm_plan_label));
		gtk_widget_hide (GTK_WIDGET (priv->confirm_plan));
	} else {
		/* Plan */
		gtk_widget_show (GTK_WIDGET (priv->confirm_plan_label));
		gtk_widget_show (GTK_WIDGET (priv->confirm_plan));

		if (method)
			gtk_label_set_text (priv->confirm_plan, nma_mobile_access_method_get_name (method));
		else
			gtk_label_set_text (priv->confirm_plan, _("Unlisted"));

		apn = gtk_editable_get_text (priv->plan_apn_entry);
	}

	if (apn) {
		str = g_string_new (NULL);
		g_string_append_printf (str, "<span color=\"#999999\">APN: %s</span>", apn);
		gtk_label_set_markup (priv->confirm_apn, str->str);
		g_string_free (str, TRUE);
		gtk_widget_show (GTK_WIDGET (priv->confirm_apn));
	} else {
		gtk_widget_hide (GTK_WIDGET (priv->confirm_apn));
	}
}

/**********************************************************/
/* Plan page */
/**********************************************************/

#define PLAN_COL_NAME 0
#define PLAN_COL_METHOD 1
#define PLAN_COL_MANUAL 2

static NMAMobileAccessMethod *
get_selected_method (NMAMobileWizard *self, gboolean *manual)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	GtkTreeModel *model;
	NMAMobileAccessMethod *method = NULL;
	GtkTreeIter iter;
	gboolean is_manual = FALSE;

	if (!gtk_combo_box_get_active_iter (priv->plan_combo, &iter))
		return NULL;

	model = gtk_combo_box_get_model (priv->plan_combo);
	if (!model)
		return NULL;

	gtk_tree_model_get (model, &iter,
	                    PLAN_COL_METHOD, &method,
	                    PLAN_COL_MANUAL, &is_manual,
	                    -1);
	if (is_manual) {
		if (manual)
			*manual = is_manual;
		if (method)
			nma_mobile_access_method_unref (method);
		method = NULL;
	}

	return method;
}

static void
plan_update_complete (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	GtkAssistant *assistant = GTK_ASSISTANT (self);
	gboolean is_manual = FALSE;
	NMAMobileAccessMethod *method;

	method = get_selected_method (self, &is_manual);
	if (method) {
		gtk_assistant_set_page_complete (assistant, priv->plan_page, TRUE);
		nma_mobile_access_method_unref (method);
	} else {
		const char *manual_apn;

		manual_apn = gtk_editable_get_text (priv->plan_apn_entry);
		gtk_assistant_set_page_complete (assistant, priv->plan_page,
		                                 (manual_apn && strlen (manual_apn)));
	}
}

static void
plan_combo_changed (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	NMAMobileAccessMethod *method = NULL;
	gboolean is_manual = FALSE;

	method = get_selected_method (self, &is_manual);
	if (method) {
		gtk_editable_set_text (priv->plan_apn_entry, nma_mobile_access_method_get_3gpp_apn (method));
		gtk_widget_set_sensitive (GTK_WIDGET (priv->plan_apn_entry), FALSE);
	} else {
		gtk_editable_set_text (priv->plan_apn_entry, "");
		gtk_widget_set_sensitive (GTK_WIDGET (priv->plan_apn_entry), TRUE);
		gtk_widget_grab_focus (GTK_WIDGET (priv->plan_apn_entry));
	}

	if (method)
		nma_mobile_access_method_unref (method);

	plan_update_complete (self);
}

static gboolean
plan_row_separator_func (GtkTreeModel *model, GtkTreeIter *iter, gpointer data)
{
	NMAMobileAccessMethod *method = NULL;
	gboolean is_manual = FALSE;
	gboolean draw_separator = FALSE;

	gtk_tree_model_get (model, iter,
	                    PLAN_COL_METHOD, &method,
	                    PLAN_COL_MANUAL, &is_manual,
	                    -1);
	if (!method && !is_manual)
		draw_separator = TRUE;
	if (method)
		nma_mobile_access_method_unref (method);
	return draw_separator;
}

static void
apn_filter_cb (GtkEditable *editable,
               gchar *text,
               gint length,
               gint *position,
               gpointer user_data)
{
	utils_filter_editable_on_insert_text (editable,
	                                      text, length, position, user_data,
	                                      utils_char_is_ascii_apn,
	                                      apn_filter_cb);
}

static void
plan_setup (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	GtkCellRenderer *renderer;

	gtk_combo_box_set_row_separator_func (priv->plan_combo,
	                                      plan_row_separator_func,
	                                      NULL,
	                                      NULL);

	renderer = gtk_cell_renderer_text_new ();
	gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (priv->plan_combo), renderer, TRUE);
	gtk_cell_layout_add_attribute (GTK_CELL_LAYOUT (priv->plan_combo), renderer, "text", PLAN_COL_NAME);
}

static gboolean
focus_plan_apn_entry (gpointer user_data)
{
	NMAMobileWizard *self = user_data;
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	priv->plan_focus_id = 0;
	gtk_widget_grab_focus (GTK_WIDGET (priv->plan_apn_entry));
	return FALSE;
}

static void
plan_prepare (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	NMAMobileProvider *provider;
	GtkTreeIter method_iter;
	guint32 count = 0;

	gtk_tree_store_clear (priv->plan_store);

	provider = get_selected_provider (self);
	if (provider) {
		GSList *iter;

		for (iter = nma_mobile_provider_get_methods (provider); iter; iter = g_slist_next (iter)) {
			NMAMobileAccessMethod *method = iter->data;

			if (   (priv->family != NMA_MOBILE_FAMILY_UNKNOWN)
			    && (nma_mobile_access_method_get_family (method) != priv->family))
				continue;

			gtk_tree_store_append (priv->plan_store, &method_iter, NULL);
			gtk_tree_store_set (priv->plan_store,
			                    &method_iter,
			                    PLAN_COL_NAME,
			                    nma_mobile_access_method_get_name (method),
			                    PLAN_COL_METHOD,
			                    method,
			                    -1);
			count++;
		}
		nma_mobile_provider_unref (provider);

		/* Draw the separator */
		if (count)
			gtk_tree_store_append (priv->plan_store, &method_iter, NULL);
	}

	/* Add the "My plan is not listed..." item */
	gtk_tree_store_append (priv->plan_store, &method_iter, NULL);
	gtk_tree_store_set (priv->plan_store,
	                    &method_iter,
	                    PLAN_COL_NAME,
	                    _("My plan is not listed…"),
	                    PLAN_COL_MANUAL,
	                    TRUE,
	                    -1);
	/* Select the first item by default if nothing is yet selected */
	if (gtk_combo_box_get_active (priv->plan_combo) < 0)
		gtk_combo_box_set_active (priv->plan_combo, 0);

	gtk_widget_set_sensitive (GTK_WIDGET (priv->plan_combo), count > 0);
	if (count == 0) {
		if (!priv->plan_focus_id)
			priv->plan_focus_id = g_idle_add (focus_plan_apn_entry, self);
	}

	plan_combo_changed (self);
}

/**********************************************************/
/* Providers page */
/**********************************************************/

#define PROVIDER_COL_NAME 0
#define PROVIDER_COL_PROVIDER 1

static gboolean
providers_search_func (GtkTreeModel *model,
                       gint column,
                       const char *key,
                       GtkTreeIter *iter,
                       gpointer search_data)
{
	gboolean unmatched = TRUE;
	char *provider = NULL;

	if (!key)
		return TRUE;

	gtk_tree_model_get (model, iter, column, &provider, -1);
	if (!provider)
		return TRUE;

	unmatched = !!g_ascii_strncasecmp (provider, key, strlen (key));
	g_free (provider);
	return unmatched;
}

static NMAMobileProvider *
get_selected_provider (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	GtkTreeSelection *selection;
	GtkTreeModel *model = NULL;
	GtkTreeIter iter;
	NMAMobileProvider *provider = NULL;

	if (!gtk_toggle_button_get_active (priv->providers_view_radio))
		return NULL;

	selection = gtk_tree_view_get_selection (priv->providers_view);
	g_assert (selection);

	if (!gtk_tree_selection_get_selected (GTK_TREE_SELECTION (selection), &model, &iter))
		return NULL;

	gtk_tree_model_get (model, &iter, PROVIDER_COL_PROVIDER, &provider, -1);
	return provider;
}

static void
providers_update_complete (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	GtkAssistant *assistant = GTK_ASSISTANT (self);
	gboolean use_view;

	use_view = gtk_toggle_button_get_active (priv->providers_view_radio);
	if (use_view) {
		NMAMobileProvider *provider;

		provider = get_selected_provider (self);
		gtk_assistant_set_page_complete (assistant, priv->providers_page, !!provider);
		if (provider)
			nma_mobile_provider_unref (provider);
	} else {
		gtk_assistant_set_page_complete (assistant, priv->providers_page, TRUE);
	}
}

static void
providers_update_continue (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	gtk_assistant_set_page_complete (GTK_ASSISTANT (self),
	                                 priv->providers_page,
	                                 TRUE);

	gtk_assistant_next_page (GTK_ASSISTANT (self));
}

static gboolean
focus_providers_view (gpointer user_data)
{
	NMAMobileWizard *self = user_data;
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	priv->providers_focus_id = 0;
	gtk_widget_grab_focus (GTK_WIDGET (priv->providers_view));
	return FALSE;
}

static gboolean
focus_provider_unlisted_type_combo (gpointer user_data)
{
	NMAMobileWizard *self = user_data;
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	priv->providers_focus_id = 0;
	gtk_widget_grab_focus (GTK_WIDGET (priv->provider_unlisted_type_combo));
	return FALSE;
}

static void
providers_radio_toggled (GtkToggleButton *button, gpointer user_data)
{
	NMAMobileWizard *self = user_data;
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	gboolean use_view;

	use_view = gtk_toggle_button_get_active (priv->providers_view_radio);
	if (use_view) {
		if (!priv->providers_focus_id)
			priv->providers_focus_id = g_idle_add (focus_providers_view, self);
		gtk_widget_set_sensitive (GTK_WIDGET (priv->providers_view), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (priv->provider_unlisted_type_combo), FALSE);
	} else if (priv->family == NMA_MOBILE_FAMILY_UNKNOWN) {
		if (!priv->providers_focus_id)
			priv->providers_focus_id = g_idle_add (focus_provider_unlisted_type_combo, self);
		gtk_widget_set_sensitive (GTK_WIDGET (priv->providers_view), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (priv->provider_unlisted_type_combo), TRUE);
	}

	providers_update_complete (self);
}

static NMAMobileFamily
get_provider_unlisted_type (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	switch (gtk_combo_box_get_active (priv->provider_unlisted_type_combo)) {
	case 0:
		return NMA_MOBILE_FAMILY_3GPP;
	case 1:
		return NMA_MOBILE_FAMILY_CDMA;
	default:
		g_return_val_if_reached (NMA_MOBILE_FAMILY_UNKNOWN);
	}
}

static void
providers_setup (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeSelection *selection;

	gtk_tree_sortable_set_sort_column_id (GTK_TREE_SORTABLE (priv->providers_sort),
	                                      PROVIDER_COL_NAME, GTK_SORT_ASCENDING);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes (_("Provider"),
	                                                   renderer,
	                                                   "text", PROVIDER_COL_NAME,
	                                                   NULL);
	gtk_tree_view_append_column (priv->providers_view, column);
	gtk_tree_view_column_set_clickable (column, TRUE);

	selection = gtk_tree_view_get_selection (priv->providers_view);
	g_assert (selection);

	switch (priv->family) {
	case NMA_MOBILE_FAMILY_3GPP:
		gtk_combo_box_set_active (priv->provider_unlisted_type_combo, 0);
		gtk_widget_set_sensitive (GTK_WIDGET (priv->provider_unlisted_type_combo), FALSE);
		break;
	case NMA_MOBILE_FAMILY_CDMA:
		gtk_combo_box_set_active (priv->provider_unlisted_type_combo, 1);
		gtk_widget_set_sensitive (GTK_WIDGET (priv->provider_unlisted_type_combo), FALSE);
		break;
	case NMA_MOBILE_FAMILY_UNKNOWN:
		gtk_widget_set_sensitive (GTK_WIDGET (priv->provider_unlisted_type_combo), TRUE);
		break;
	}
}

static void
providers_prepare (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	GtkTreeSelection *selection;
	NMACountryInfo *country_info;
	GSList *piter;

	gtk_tree_store_clear (priv->providers_store);

	country_info = get_selected_country (self);
	for (piter = nma_country_info_get_providers (country_info);
	     piter;
	     piter = g_slist_next (piter)) {
		NMAMobileProvider *provider = piter->data;
		GtkTreeIter provider_iter;

		/* Ignore providers that don't match the current device type */
		if (priv->family != NMA_MOBILE_FAMILY_UNKNOWN) {
			GSList *miter;
			guint32 count = 0;

			for (miter = nma_mobile_provider_get_methods (provider); miter; miter = g_slist_next (miter)) {
				NMAMobileAccessMethod *method = miter->data;

				if (priv->family == nma_mobile_access_method_get_family (method))
					count++;
			}

			if (!count)
				continue;
		}

		gtk_tree_store_append (priv->providers_store, &provider_iter, NULL);
		gtk_tree_store_set (priv->providers_store,
		                    &provider_iter,
		                    PROVIDER_COL_NAME,
		                    nma_mobile_provider_get_name (provider),
		                    PROVIDER_COL_PROVIDER,
		                    provider,
		                    -1);
	}
	nma_country_info_unref (country_info);

	gtk_tree_view_set_search_column (priv->providers_view, PROVIDER_COL_NAME);
	gtk_tree_view_set_search_equal_func (priv->providers_view,
	                                     providers_search_func, self, NULL);

	/* If no row has focus yet, focus the first row so that the user can start
	 * incremental search without clicking.
	 */
	selection = gtk_tree_view_get_selection (priv->providers_view);
	g_assert (selection);
	if (!gtk_tree_selection_count_selected_rows (selection)) {
		GtkTreeIter first_iter;
		GtkTreePath *first_path;

		if (gtk_tree_model_get_iter_first (priv->providers_sort, &first_iter)) {
			first_path = gtk_tree_model_get_path (priv->providers_sort, &first_iter);
			if (first_path) {
				gtk_tree_selection_select_path (selection, first_path);
				gtk_tree_path_free (first_path);
			}
		}
	}

	if (gtk_tree_model_iter_n_children (GTK_TREE_MODEL (priv->providers_store), NULL) == 0) {
		/* No providers to choose from. */
		gtk_toggle_button_set_active (priv->provider_unlisted_radio, TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (priv->providers_view_radio), FALSE);
	} else {
		gtk_toggle_button_set_active (priv->providers_view_radio, TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (priv->providers_view_radio), TRUE);
	}

	providers_radio_toggled (NULL, self);

	/* Initial completeness state */
	providers_update_complete (self);
}

/**********************************************************/
/* Country page */
/**********************************************************/

#define COUNTRIES_COL_NAME 0
#define COUNTRIES_COL_INFO 1

static gboolean
country_search_func (GtkTreeModel *model,
                     gint column,
                     const char *key,
                     GtkTreeIter *iter,
                     gpointer search_data)
{
	gboolean unmatched = TRUE;
	char *country = NULL;

	if (!key)
		return TRUE;

	gtk_tree_model_get (model, iter, column, &country, -1);
	if (!country)
		return TRUE;

	unmatched = !!g_ascii_strncasecmp (country, key, strlen (key));
	g_free (country);
	return unmatched;
}

static void
add_one_country (gpointer key, gpointer value, gpointer user_data)
{
	NMAMobileWizard *self = user_data;
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	NMACountryInfo *country_info = value;
	GtkTreeIter country_iter;
	GtkTreePath *country_path, *country_view_path;

	g_assert (key);

	if (   nma_country_info_get_country_code (country_info)
	    && !nma_country_info_get_providers (country_info))
		return;

	gtk_tree_store_append (priv->country_store, &country_iter, NULL);
	gtk_tree_store_set (priv->country_store,
	                    &country_iter,
	                    COUNTRIES_COL_NAME,
	                    nma_country_info_get_country_name (country_info),
	                    COUNTRIES_COL_INFO,
	                    country_info,
	                    -1);

	/* If this country is the same country as the user's current locale,
	 * select it by default.
	 */
	if (priv->country != country_info)
		return;

	country_path = gtk_tree_model_get_path (GTK_TREE_MODEL (priv->country_store), &country_iter);
	if (!country_path)
		return;

	country_view_path = gtk_tree_model_sort_convert_child_path_to_path (priv->country_sort, country_path);
	if (country_view_path) {
		GtkTreeSelection *selection;

		gtk_tree_view_expand_row (priv->country_view, country_view_path, TRUE);

		selection = gtk_tree_view_get_selection (priv->country_view);
		g_assert (selection);
		gtk_tree_selection_select_path (selection, country_view_path);
		gtk_tree_view_scroll_to_cell (priv->country_view,
		                              country_view_path, NULL, TRUE, 0, 0);
		gtk_tree_path_free (country_view_path);
	}
	gtk_tree_path_free (country_path);
}

static NMACountryInfo *
get_selected_country (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	GtkTreeSelection *selection;
	GtkTreeModel *model = NULL;
	GtkTreeIter iter;
	NMACountryInfo *country_info = NULL;

	selection = gtk_tree_view_get_selection (priv->country_view);
	g_assert (selection);

	if (!gtk_tree_selection_get_selected (GTK_TREE_SELECTION (selection), &model, &iter))
		return NULL;

	gtk_tree_model_get (model, &iter, COUNTRIES_COL_INFO, &country_info, -1);
	return country_info;
}

static void
country_update_complete (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	GtkTreeSelection *selection;

	selection = gtk_tree_view_get_selection (priv->country_view);
	g_assert (selection);

	gtk_assistant_set_page_complete (GTK_ASSISTANT (self),
	                                 priv->country_page,
	                                 gtk_tree_selection_get_selected (selection, NULL, NULL));
}

static void
country_update_continue (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	gtk_assistant_set_page_complete (GTK_ASSISTANT (self),
	                                 priv->country_page,
	                                 TRUE);

	gtk_assistant_next_page (GTK_ASSISTANT (self));
}

static gint
country_sort_func (GtkTreeModel *model,
                   GtkTreeIter *a,
                   GtkTreeIter *b,
                   gpointer user_data)
{
	char *a_str = NULL, *b_str = NULL;
	NMACountryInfo *a_country_info = NULL, *b_country_info = NULL;
	gint ret = 0;

	gtk_tree_model_get (model, a, COUNTRIES_COL_NAME, &a_str, COUNTRIES_COL_INFO, &a_country_info, -1);
	gtk_tree_model_get (model, b, COUNTRIES_COL_NAME, &b_str, COUNTRIES_COL_INFO, &b_country_info, -1);

	if (!a_country_info || !nma_country_info_get_country_code (a_country_info)) {
		ret = -1;
		goto out;
	} else if (!b_country_info || !nma_country_info_get_country_code (b_country_info)) {
		ret = 1;
		goto out;
	}

	if (a_str && !b_str)
		ret = -1;
	else if (!a_str && b_str)
		ret = 1;
	else if (!a_str && !b_str)
		ret = 0;
	else
		ret = g_utf8_collate (a_str, b_str);

out:
	if (a_country_info)
		nma_country_info_unref (a_country_info);
	if (b_country_info)
		nma_country_info_unref (b_country_info);
	g_free (a_str);
	g_free (b_str);
	return ret;
}

static void
country_setup (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeSelection *selection;

	gtk_tree_sortable_set_sort_column_id (GTK_TREE_SORTABLE (priv->country_sort),
	                                      COUNTRIES_COL_NAME, GTK_SORT_ASCENDING);

	gtk_tree_sortable_set_sort_func (GTK_TREE_SORTABLE (priv->country_sort),
	                                 COUNTRIES_COL_NAME,
	                                 country_sort_func,
	                                 NULL,
	                                 NULL);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes (NULL,
	                                                   renderer,
	                                                   "text", COUNTRIES_COL_NAME,
	                                                   NULL);
	gtk_tree_view_append_column (priv->country_view, column);
	gtk_tree_view_column_set_clickable (column, TRUE);

	/* Add the rest of the providers */
	if (priv->mobile_providers_database) {
		GHashTable *countries;

		countries = nma_mobile_providers_database_get_countries (priv->mobile_providers_database);
		g_hash_table_foreach (countries, add_one_country, self);
	}

	/* If no row has focus yet, focus the first row so that the user can start
	 * incremental search without clicking.
	 */
	selection = gtk_tree_view_get_selection (priv->country_view);
	g_assert (selection);
	if (!gtk_tree_selection_count_selected_rows (selection)) {
		GtkTreeIter first_iter;
		GtkTreePath *first_path;

		if (gtk_tree_model_get_iter_first (GTK_TREE_MODEL (priv->country_sort), &first_iter)) {
			first_path = gtk_tree_model_get_path (GTK_TREE_MODEL (priv->country_sort), &first_iter);
			if (first_path) {
				gtk_tree_selection_select_path (selection, first_path);
				gtk_tree_path_free (first_path);
			}
		}
	}

	/* Initial completeness state */
	country_update_complete (self);
}

static gboolean
focus_country_view (gpointer user_data)
{
	NMAMobileWizard *self = user_data;
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	priv->country_focus_id = 0;
	gtk_widget_grab_focus (GTK_WIDGET (priv->country_view));
	return FALSE;
}

static void
country_prepare (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	gtk_tree_view_set_search_column (priv->country_view, COUNTRIES_COL_NAME);
	gtk_tree_view_set_search_equal_func (priv->country_view, country_search_func, self, NULL);

	if (!priv->country_focus_id)
		priv->country_focus_id = g_idle_add (focus_country_view, self);

	country_update_complete (self);
}

/**********************************************************/
/* Intro page */
/**********************************************************/

#define INTRO_COL_NAME 0
#define INTRO_COL_DEVICE 1
#define INTRO_COL_SEPARATOR 2

static gboolean
__intro_device_added (NMAMobileWizard *self, NMDevice *device, gboolean select_it)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	GtkTreeIter iter;
	const char *desc = nm_device_get_description (device);
	NMDeviceModemCapabilities caps;

	if (!NM_IS_DEVICE_MODEM (device))
		return FALSE;

	caps = nm_device_modem_get_current_capabilities (NM_DEVICE_MODEM (device));
	if (caps & NM_DEVICE_MODEM_CAPABILITY_GSM_UMTS) {
		if (!desc)
			desc = _("Installed GSM device");
	} else if (caps & NM_DEVICE_MODEM_CAPABILITY_CDMA_EVDO) {
		if (!desc)
			desc = _("Installed CDMA device");
	} else
		return FALSE;

	gtk_tree_store_append (priv->dev_store, &iter, NULL);
	gtk_tree_store_set (priv->dev_store,
	                    &iter,
	                    INTRO_COL_NAME, desc,
	                    INTRO_COL_DEVICE, device,
	                    -1);

	/* Select the device just added */
	if (select_it)
		gtk_combo_box_set_active_iter (priv->dev_combo, &iter);

	gtk_widget_set_sensitive (GTK_WIDGET (priv->dev_combo), TRUE);
	return TRUE;
}

static void
intro_device_added_cb (NMClient *client, NMDevice *device, NMAMobileWizard *self)
{
	__intro_device_added (self, device, TRUE);
}

static void
intro_device_removed_cb (NMClient *client, NMDevice *device, NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	GtkTreeIter iter;
	gboolean have_device = FALSE, removed = FALSE;

	if (!gtk_tree_model_get_iter_first (GTK_TREE_MODEL (priv->dev_store), &iter))
		return;

	do {
		NMDevice *candidate = NULL;

		gtk_tree_model_get (GTK_TREE_MODEL (priv->dev_store), &iter,
		                    INTRO_COL_DEVICE, &candidate, -1);
		if (candidate) {
			if (candidate == device) {
				gtk_tree_store_remove (priv->dev_store, &iter);
				removed = TRUE;
			}
			g_object_unref (candidate);
		}
	} while (!removed && gtk_tree_model_iter_next (GTK_TREE_MODEL (priv->dev_store), &iter));

	/* There's already a selected device item; nothing more to do */
	if (gtk_combo_box_get_active (priv->dev_combo) > 1)
		return;

	/* If there are no more devices, select the "Any" item and disable the
	 * combo box.  If there is no selected item and there is at least one device
	 * item, select the first one.
	 */
	if (!gtk_tree_model_get_iter_first (GTK_TREE_MODEL (priv->dev_store), &iter))
		return;

	do {
		NMDevice *candidate = NULL;

		gtk_tree_model_get (GTK_TREE_MODEL (priv->dev_store), &iter,
		                    INTRO_COL_DEVICE, &candidate, -1);
		if (candidate) {
			have_device = TRUE;
			g_object_unref (candidate);
		}
	} while (!have_device && gtk_tree_model_iter_next (GTK_TREE_MODEL (priv->dev_store), &iter));

	if (have_device) {
		/* Iter should point to the last device item in the combo */
		gtk_combo_box_set_active_iter (priv->dev_combo, &iter);
	} else {
		gtk_combo_box_set_active (priv->dev_combo, 0);
		gtk_widget_set_sensitive (GTK_WIDGET (priv->dev_combo), FALSE);
	}
}

static void
intro_add_initial_devices (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	const GPtrArray *devices;
	gboolean selected_first = FALSE;
	int i;

	devices = priv->client ? nm_client_get_devices (priv->client) : NULL;
	for (i = 0; devices && (i < devices->len); i++) {
		if (__intro_device_added (self, g_ptr_array_index (devices, i), !selected_first)) {
			if (selected_first == FALSE)
				selected_first = TRUE;
		}
	}

	/* Otherwise the "Any device" item */
	if (!selected_first) {
		/* Select the first device item by default */
		gtk_combo_box_set_active (priv->dev_combo, 0);
		gtk_widget_set_sensitive (GTK_WIDGET (priv->dev_combo), FALSE);
	}
}

static void
intro_remove_all_devices (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	gtk_tree_store_clear (priv->dev_store);

	/* Select the "Any device" item */
	gtk_combo_box_set_active (priv->dev_combo, 0);
}

static void
intro_manager_running_cb (NMClient *client, GParamSpec *pspec, NMAMobileWizard *self)
{
	if (nm_client_get_nm_running (client))
		intro_add_initial_devices (self);
	else
		intro_remove_all_devices (self);
}

static gboolean
intro_row_separator_func (GtkTreeModel *model, GtkTreeIter *iter, gpointer data)
{
	gboolean separator = FALSE;
	gtk_tree_model_get (model, iter, INTRO_COL_SEPARATOR, &separator, -1);
	return separator;
}

static void
intro_combo_changed (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	GtkTreeIter iter;
	NMDevice *selected = NULL;
	NMDeviceModemCapabilities caps;

	g_free (priv->dev_desc);
	priv->dev_desc = NULL;

	if (!gtk_combo_box_get_active_iter (priv->dev_combo, &iter))
		return;

	gtk_tree_model_get (GTK_TREE_MODEL (priv->dev_store), &iter,
	                    INTRO_COL_DEVICE, &selected, -1);
	if (selected) {
		priv->dev_desc = g_strdup (nm_device_get_description (selected));
		caps = nm_device_modem_get_current_capabilities (NM_DEVICE_MODEM (selected));
		if (caps & NM_DEVICE_MODEM_CAPABILITY_GSM_UMTS)
			priv->family = NMA_MOBILE_FAMILY_3GPP;
		else if (caps & NM_DEVICE_MODEM_CAPABILITY_CDMA_EVDO)
			priv->family = NMA_MOBILE_FAMILY_CDMA;
		else
			g_warning ("%s: unknown modem capabilities 0x%X", __func__, caps);

		g_object_unref (selected);
	}
}

static void
intro_setup (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);
	GtkCellRenderer *renderer;
	char *s;

        s = g_strdup_printf ("• %s", gtk_label_get_text (priv->provider_name_label));
	gtk_label_set_text (priv->provider_name_label, s);
	g_free (s);

        s = g_strdup_printf ("• %s", gtk_label_get_text (priv->plan_name_label));
	gtk_label_set_text (priv->plan_name_label, s);
	g_free (s);

        s = g_strdup_printf ("• %s", gtk_label_get_text (priv->apn_label));
	gtk_label_set_text (priv->apn_label, s);
	g_free (s);

	/* Device combo; only built if the wizard's caller didn't pass one in */
	if (!priv->initial_family) {
		GtkTreeIter iter;

		priv->client = nm_client_new (NULL, NULL);
		if (priv->client) {
			g_signal_connect (priv->client, "device-added",
			                  G_CALLBACK (intro_device_added_cb), self);
			g_signal_connect (priv->client, "device-removed",
			                  G_CALLBACK (intro_device_removed_cb), self);
			g_signal_connect (priv->client, "notify::manager-running",
			                  G_CALLBACK (intro_manager_running_cb), self);
		}

		gtk_combo_box_set_row_separator_func (priv->dev_combo,
		                                      intro_row_separator_func, NULL, NULL);

		renderer = gtk_cell_renderer_text_new ();
		gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (priv->dev_combo), renderer, TRUE);
		gtk_cell_layout_add_attribute (GTK_CELL_LAYOUT (priv->dev_combo), renderer, "text", INTRO_COL_NAME);

		/* Any device */
		gtk_tree_store_append (priv->dev_store, &iter, NULL);
		gtk_tree_store_set (priv->dev_store, &iter,
		                    INTRO_COL_NAME, _("Any device"), -1);

		/* Separator */
		gtk_tree_store_append (priv->dev_store, &iter, NULL);
		gtk_tree_store_set (priv->dev_store, &iter,
		                    INTRO_COL_SEPARATOR, TRUE, -1);

		intro_add_initial_devices (self);
	}
}

/**********************************************************/
/* General assistant stuff */
/**********************************************************/

static void
remove_plan_focus_idle (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	if (priv->plan_focus_id) {
		g_source_remove (priv->plan_focus_id);
		priv->plan_focus_id = 0;
	}
}

static void
remove_provider_focus_idle (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	if (priv->providers_focus_id) {
		g_source_remove (priv->providers_focus_id);
		priv->providers_focus_id = 0;
	}
}

static void
remove_country_focus_idle (NMAMobileWizard *self)
{
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	if (priv->country_focus_id) {
		g_source_remove (priv->country_focus_id);
		priv->country_focus_id = 0;
	}
}

static void
assistant_prepare (GtkAssistant *assistant, GtkWidget *page, gpointer user_data)
{
	NMAMobileWizard *self = user_data;
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	if (page != priv->plan_page)
		remove_plan_focus_idle (self);
	if (page != priv->providers_page)
		remove_provider_focus_idle (self);
	if (page != priv->country_page)
		remove_country_focus_idle (self);

	if (page == priv->country_page)
		country_prepare (self);
	else if (page == priv->providers_page)
		providers_prepare (self);
	else if (page == priv->plan_page)
		plan_prepare (self);
	else if (page == priv->confirm_page)
		confirm_prepare (self);
}

static gint
forward_func (gint current_page, gpointer user_data)
{
	NMAMobileWizard *self = user_data;
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	if (current_page == PROVIDERS_PAGE_IDX) {
		NMAMobileFamily family = priv->family;

		/* If the provider is unlisted, we can skip ahead of the user's
		 * access technology is CDMA.
		 */
		if (gtk_toggle_button_get_active (priv->provider_unlisted_radio)) {
			if (family == NMA_MOBILE_FAMILY_UNKNOWN)
				family = get_provider_unlisted_type (self);
		} else {
			/* Or, if the provider is only CDMA, then we can also skip ahead */
			NMAMobileProvider *provider;
			GSList *iter;
			gboolean gsm = FALSE, cdma = FALSE;

			provider = get_selected_provider (self);
			if (provider) {
				for (iter = nma_mobile_provider_get_methods (provider); iter; iter = g_slist_next (iter)) {
					NMAMobileAccessMethod *method = iter->data;

					if (nma_mobile_access_method_get_family (method) == NMA_MOBILE_FAMILY_CDMA)
						cdma = TRUE;
					else if (nma_mobile_access_method_get_family (method) == NMA_MOBILE_FAMILY_3GPP)
						gsm = TRUE;
				}
				nma_mobile_provider_unref (provider);

				if (cdma && !gsm)
					family = NMA_MOBILE_FAMILY_CDMA;
			}
		}

		/* Skip to the confirm page if we know its CDMA */
		if (family == NMA_MOBILE_FAMILY_CDMA) {
			priv->provider_only_cdma = TRUE;
			return CONFIRM_PAGE_IDX;
		} else
			priv->provider_only_cdma = FALSE;
	}

	return current_page + 1;
}

static char *
get_country_from_locale (void)
{
	char *p, *m, *cc, *lang;

	lang = getenv ("LC_ALL");
	if (!lang)
		lang = getenv ("LANG");
	if (!lang)
		return NULL;

	p = strchr (lang, '_');
	if (!p || !strlen (p)) {
		g_free (p);
		return NULL;
	}

	p = cc = g_strdup (++p);
	m = strchr (cc, '.');
	if (m)
		*m = '\0';

	while (*p) {
		*p = g_ascii_toupper (*p);
		p++;
	}

	return cc;
}

static void
finalize (GObject *object)
{
	NMAMobileWizard *self = NMA_MOBILE_WIZARD (object);
	NMAMobileWizardPrivate *priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	g_clear_pointer (&priv->dev_desc, g_free);
	g_clear_object (&priv->client);

	remove_plan_focus_idle (self);
	remove_provider_focus_idle (self);
	remove_country_focus_idle (self);

	g_clear_object (&priv->mobile_providers_database);

	G_OBJECT_CLASS (nma_mobile_wizard_parent_class)->finalize (object);
}

static void
nma_mobile_wizard_class_init (NMAMobileWizardClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	object_class->finalize = finalize;

	g_type_ensure (NM_TYPE_DEVICE);
	gtk_widget_class_set_template_from_resource (widget_class,
	                                             "/org/freedesktop/network-manager-applet/nma-mobile-wizard.ui");


	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, dev_combo);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, dev_combo_label);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, country_page);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, country_view);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, providers_page);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, providers_view_radio);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, providers_view);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, provider_unlisted_radio);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, provider_unlisted_type_combo);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, plan_page);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, plan_combo);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, plan_apn_entry);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, confirm_page);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, confirm_provider);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, confirm_plan_label);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, confirm_apn);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, confirm_plan);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, confirm_device_label);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, confirm_connect_after_label);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, confirm_device);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, provider_name_label);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, plan_name_label);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, apn_label);

	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, dev_store);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, country_store);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, country_sort);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, providers_store);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, providers_sort);
	gtk_widget_class_bind_template_child_private (widget_class, NMAMobileWizard, plan_store);

	gtk_widget_class_bind_template_callback (widget_class, assistant_closed);
	gtk_widget_class_bind_template_callback (widget_class, assistant_cancel);
	gtk_widget_class_bind_template_callback (widget_class, assistant_prepare);
	gtk_widget_class_bind_template_callback (widget_class, intro_combo_changed);
	gtk_widget_class_bind_template_callback (widget_class, country_update_continue);
	gtk_widget_class_bind_template_callback (widget_class, providers_radio_toggled);
	gtk_widget_class_bind_template_callback (widget_class, providers_update_complete);
	gtk_widget_class_bind_template_callback (widget_class, providers_update_continue);
	gtk_widget_class_bind_template_callback (widget_class, plan_combo_changed);
	gtk_widget_class_bind_template_callback (widget_class, plan_update_complete);
	gtk_widget_class_bind_template_callback (widget_class, apn_filter_cb);
}

static void
nma_mobile_wizard_init (NMAMobileWizard *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));
	gtk_widget_realize (GTK_WIDGET (self));

	if (GDK_IS_X11_DISPLAY (gtk_widget_get_display (GTK_WIDGET (self)))) {
#if GTK_CHECK_VERSION(3,90,0)
		GdkSurface *surface = gtk_widget_get_surface (GTK_WIDGET (self));
		gdk_x11_surface_set_skip_taskbar_hint (surface, TRUE);
#else
		GdkWindow *gdk_window = gtk_widget_get_window (GTK_WIDGET (self));
		gdk_window_set_skip_taskbar_hint (gdk_window, TRUE);
#endif
	}
}

/**
 * nma_mobile_wizard_new: (skip)
 * @parent:
 * @window_group:
 * @modem_caps:
 * @will_connect_after:
 * @cb: (scope async):
 * @user_data:
 *
 * Returns: the newly created #NMAMobileWizard
 */
NMAMobileWizard *
nma_mobile_wizard_new (GtkWindow *parent,
                       GtkWindowGroup *window_group,
                       NMDeviceModemCapabilities modem_caps,
                       gboolean will_connect_after,
                       NMAMobileWizardCallback cb,
                       gpointer user_data)
{
	NMAMobileWizard *self;
	NMAMobileWizardPrivate *priv;
	char *cc;
	GError *error = NULL;

	self = g_object_new (NMA_TYPE_MOBILE_WIZARD, NULL);
	priv = NMA_MOBILE_WIZARD_GET_PRIVATE (self);

	priv->mobile_providers_database = nma_mobile_providers_database_new_sync (NULL, NULL, NULL, &error);
	if (!priv->mobile_providers_database) {
		g_warning ("Cannot create mobile providers database: %s",
		           error->message);
		g_error_free (error);
		nma_mobile_wizard_destroy (self);
		return NULL;
	}

	cc = get_country_from_locale ();
	if (cc) {
		priv->country = nma_mobile_providers_database_lookup_country (priv->mobile_providers_database, cc);
		g_free (cc);
	}

	priv->will_connect_after = will_connect_after;
	priv->callback = cb;
	priv->user_data = user_data;
	if (modem_caps & NM_DEVICE_MODEM_CAPABILITY_GSM_UMTS)
		priv->family = NMA_MOBILE_FAMILY_3GPP;
	else if (modem_caps & NM_DEVICE_MODEM_CAPABILITY_CDMA_EVDO)
		priv->family = NMA_MOBILE_FAMILY_CDMA;
	if (priv->family) {
		priv->initial_family = TRUE;  /* Skip device selection */
	} else {
		gtk_widget_show (GTK_WIDGET (priv->dev_combo_label));
		gtk_widget_show (GTK_WIDGET (priv->dev_combo));
	}

	gtk_assistant_set_forward_page_func (GTK_ASSISTANT (self),
	                                     forward_func, self, NULL);

	intro_setup (self);
	country_setup (self);
	providers_setup (self);
	plan_setup (self);
	confirm_setup (self);

	if (parent)
		gtk_window_set_transient_for (GTK_WINDOW (self), parent);
	if (window_group)
		gtk_window_group_add_window (window_group, GTK_WINDOW (self));

	return self;
}

void
nma_mobile_wizard_present (NMAMobileWizard *self)
{
	g_return_if_fail (self != NULL);

	gtk_window_present (GTK_WINDOW (self));
}

void
nma_mobile_wizard_destroy (NMAMobileWizard *self)
{
	g_return_if_fail (self != NULL);

	gtk_widget_destroy (GTK_WIDGET (self));
}
