/* NetworkManager Applet -- allow user control over networking
 *
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
