// SPDX-License-Identifier: LGPL-2.1+
/* NetworkManager Applet -- allow user control over networking
 *
 * Lubomir Rintel <lkundrak@v3.sk>
 *
 * Copyright (C) 2016,2017 Red Hat, Inc.
 */

#ifndef __NMA_PKCS11_CERT_CHOOSER_DIALOG_H__
#define __NMA_PKCS11_CERT_CHOOSER_DIALOG_H__

#include <gtk/gtk.h>
#include <gck/gck.h>

typedef struct _NMAPkcs11CertChooserDialogPrivate NMAPkcs11CertChooserDialogPrivate;

typedef struct {
        GtkDialog parent;
	NMAPkcs11CertChooserDialogPrivate *priv;
} NMAPkcs11CertChooserDialog;

typedef struct {
        GtkDialogClass parent;
} NMAPkcs11CertChooserDialogClass;

#define NMA_TYPE_PKCS11_CERT_CHOOSER_DIALOG            (nma_pkcs11_cert_chooser_dialog_get_type ())
#define NMA_PKCS11_CERT_CHOOSER_DIALOG(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), NMA_TYPE_PKCS11_CERT_CHOOSER_DIALOG, NMAPkcs11CertChooserDialog))
#define NMA_PKCS11_CERT_CHOOSER_DIALOG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), NMA_TYPE_PKCS11_CERT_CHOOSER_DIALOG, NMAPkcs11CertChooserDialogClass))
#define NMA_IS_PKCS11_CERT_CHOOSER_DIALOG(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), NMA_TYPE_PKCS11_CERT_CHOOSER_DIALOG))
#define NMA_IS_PKCS11_CERT_CHOOSER_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), NMA_TYPE_PKCS11_CERT_CHOOSER_DIALOG))
#define NMA_PKCS11_CERT_CHOOSER_DIALOG_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), NMA_TYPE_PKCS11_CERT_CHOOSER_DIALOG, NMAPkcs11CertChooserDialogClass))

GType nma_pkcs11_cert_chooser_dialog_get_type (void);

GtkWidget *nma_pkcs11_cert_chooser_dialog_new (GckSlot *slot,
                                               CK_OBJECT_CLASS object_class,
                                               const gchar *title,
                                               GtkWindow *parent,
                                               GtkDialogFlags flags,
                                               const gchar *first_button_text,
                                               ...);

gchar *nma_pkcs11_cert_chooser_dialog_get_uri (NMAPkcs11CertChooserDialog *dialog);

gchar *nma_pkcs11_cert_chooser_dialog_get_pin (NMAPkcs11CertChooserDialog *dialog);

gboolean nma_pkcs11_cert_chooser_dialog_get_remember_pin (NMAPkcs11CertChooserDialog *dialog);

#endif /* __NMA_PKCS11_CERT_CHOOSER_DIALOG_H__ */
