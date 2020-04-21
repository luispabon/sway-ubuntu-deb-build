// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Applet -- allow user control over networking
 *
 * Copyright 2015, 2018 Red Hat, Inc.
 */

#include "nm-default.h"

#include "ce-utils.h"

/* Change key in @event to 'Enter' key. */
void
utils_fake_return_key (GdkEventKey *event)
{
	GdkKeymapKey *keys = NULL;
	gint n_keys;

	/* Get hardware keycode for GDK_KEY_Return */
	if (gdk_keymap_get_entries_for_keyval (gdk_keymap_get_default (), GDK_KEY_Return, &keys, &n_keys)) {
		event->keyval = GDK_KEY_Return;
		event->hardware_keycode = keys[0].keycode;
		event->state = 0;
	}
	g_free (keys);
}
