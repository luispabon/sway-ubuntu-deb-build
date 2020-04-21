// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Connection editor -- Connection editor for NetworkManager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2009 - 2017 Red Hat, Inc.
 */

#ifndef __CE_POLKIT_BUTTON_H__
#define __CE_POLKIT_BUTTON_H__

#include <gtk/gtk.h>

#include <NetworkManager.h>

#define CE_TYPE_POLKIT_BUTTON            (ce_polkit_button_get_type ())
#define CE_POLKIT_BUTTON(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CE_TYPE_POLKIT_BUTTON, CEPolkitButton))
#define CE_POKLIT_BUTTON_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CE_TYPE_POLKIT_BUTTON, CEPolkitButtonClass))
#define CE_IS_POLKIT_BUTTON(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CE_TYPE_POLKIT_BUTTON))
#define CE_IS_POLKIT_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CE_TYPE_POLKIT_BUTTON))
#define CE_POLKIT_BUTTON_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CE_TYPE_POLKIT_BUTTON, CEPolkitButtonClass))

typedef struct {
	GtkButton parent;
} CEPolkitButton;

typedef struct {
	GtkButtonClass parent;

	/* Signals */
	void (*actionable) (CEPolkitButton *self, gboolean actionable);
	
	void (*authorized) (CEPolkitButton *self, gboolean authorized);
} CEPolkitButtonClass;

GType ce_polkit_button_get_type (void);

GtkWidget *ce_polkit_button_new (const char *label,
                                 const char *tooltip,
                                 const char *auth_tooltip,
                                 const char *icon_name,
                                 NMClient *client,
                                 NMClientPermission permission);

void ce_polkit_button_set_validation_error (CEPolkitButton *self, const char *validation_error);

gboolean ce_polkit_button_get_actionable (CEPolkitButton *button);

gboolean ce_polkit_button_get_authorized (CEPolkitButton *button);

#endif  /* __CE_POLKIT_BUTTON_H__ */

