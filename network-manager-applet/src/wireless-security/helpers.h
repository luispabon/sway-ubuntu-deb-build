// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Applet -- allow user control over networking
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * Copyright 2009 - 2014 Red Hat, Inc.
 */

#ifndef _HELPERS_H_
#define _HELPERS_H_

typedef const char * (*HelperSecretFunc)(NMSetting *);

void helper_fill_secret_entry (NMConnection *connection,
                               GtkBuilder *builder,
                               const char *entry_name,
                               GType setting_type,
                               HelperSecretFunc func);

#endif  /* _HELPERS_H_ */

