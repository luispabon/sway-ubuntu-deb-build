// SPDX-License-Identifier: LGPL-2.1+
/* NetworkManager Applet -- allow user control over networking
 *
 * Lubomir Rintel <lkundrak@v3.sk>
 *
 * Copyright (C) 2017 Red Hat, Inc.
 */

#ifndef __NMA_PKCS11_TOKEN_LOGIN_DIALOG_H__
#define __NMA_PKCS11_TOKEN_LOGIN_DIALOG_H__

#include <gtk/gtk.h>
#include <gck/gck.h>

typedef struct _NMAPkcs11TokenLoginDialogPrivate NMAPkcs11TokenLoginDialogPrivate;

typedef struct {
        GtkDialog parent;
        NMAPkcs11TokenLoginDialogPrivate *priv;
} NMAPkcs11TokenLoginDialog;

typedef struct {
        GtkDialog parent;
} NMAPkcs11TokenLoginDialogClass;

#define NMA_TYPE_PKCS11_TOKEN_LOGIN_DIALOG            (nma_pkcs11_token_login_dialog_get_type ())
#define NMA_PKCS11_TOKEN_LOGIN_DIALOG(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), NMA_TYPE_PKCS11_TOKEN_LOGIN_DIALOG, NMAPkcs11TokenLoginDialog))
#define NMA_PKCS11_TOKEN_LOGIN_DIALOG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), NMA_TYPE_PKCS11_TOKEN_LOGIN_DIALOG, NMAPkcs11TokenLoginDialogClass))
#define NMA_IS_PKCS11_TOKEN_LOGIN_DIALOG(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), NMA_TYPE_PKCS11_TOKEN_LOGIN_DIALOG))
#define NMA_IS_PKCS11_TOKEN_LOGIN_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), NMA_TYPE_PKCS11_TOKEN_LOGIN_DIALOG))
#define NMA_PKCS11_TOKEN_LOGIN_DIALOG_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), NMA_TYPE_PKCS11_TOKEN_LOGIN_DIALOG, NMAPkcs11TokenLoginDialogClass))

GType nma_pkcs11_token_login_dialog_get_type (void);

GtkWidget *nma_pkcs11_token_login_dialog_new (GckSlot *slot);

const guchar *nma_pkcs11_token_login_dialog_get_pin_value (NMAPkcs11TokenLoginDialog *self);

gulong nma_pkcs11_token_login_dialog_get_pin_length (NMAPkcs11TokenLoginDialog *self);

gboolean nma_pkcs11_token_login_dialog_get_remember_pin (NMAPkcs11TokenLoginDialog *self);

#endif /* __NMA_PKCS11_TOKEN_LOGIN_DIALOG_H__ */
