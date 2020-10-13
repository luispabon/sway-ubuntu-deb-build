include $(GLIB_MAKEFILE)

ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

AUTOMAKE_OPTIONS = subdir-objects

BUILT_SOURCES =

bin_PROGRAMS =

lib_LTLIBRARIES =

noinst_LTLIBRARIES =

check_PROGRAMS_norun =

noinst_PROGRAMS = $(check_PROGRAMS_norun)

check_PROGRAMS =

check_programs =

check_local =

TESTS =

EXTRA_DIST =

CLEANFILES =

DISTCLEANFILES =

DISTCHECK_CONFIGURE_FLAGS = \
	--disable-dependency-tracking \
	--enable-more-warnings=error \
	--with-wwan \
	--with-team


man_MANS =

pkgconfig_DATA =

pkgconfigdir = $(libdir)/pkgconfig

SUBDIRS = \
	. \
	po

dflt_cppflags = -std=gnu99

###############################################################################

icon16dir = $(datadir)/icons/hicolor/16x16/apps
icon16_DATA = \
	icons/16/nm-device-wired.png \
	icons/16/nm-no-connection.png \
	icons/16/nm-vpn-standalone-lock.png
EXTRA_DIST += $(icon16_DATA)

icon22dir = $(datadir)/icons/hicolor/22x22/apps
icon22_DATA = \
	icons/22/nm-adhoc.png \
	icons/22/nm-device-wired.png \
	icons/22/nm-device-wired-secure.png \
	icons/22/nm-device-wwan.png \
	icons/22/nm-mb-roam.png \
	icons/22/nm-no-connection.png \
	icons/22/nm-secure-lock.png \
	icons/22/nm-signal-00.png \
	icons/22/nm-signal-00-secure.png \
	icons/22/nm-signal-100.png \
	icons/22/nm-signal-100-secure.png \
	icons/22/nm-signal-25.png \
	icons/22/nm-signal-25-secure.png \
	icons/22/nm-signal-50.png \
	icons/22/nm-signal-50-secure.png \
	icons/22/nm-signal-75.png \
	icons/22/nm-signal-75-secure.png \
	icons/22/nm-stage01-connecting01.png \
	icons/22/nm-stage01-connecting02.png \
	icons/22/nm-stage01-connecting03.png \
	icons/22/nm-stage01-connecting04.png \
	icons/22/nm-stage01-connecting05.png \
	icons/22/nm-stage01-connecting06.png \
	icons/22/nm-stage01-connecting07.png \
	icons/22/nm-stage01-connecting08.png \
	icons/22/nm-stage01-connecting09.png \
	icons/22/nm-stage01-connecting10.png \
	icons/22/nm-stage01-connecting11.png \
	icons/22/nm-stage02-connecting01.png \
	icons/22/nm-stage02-connecting02.png \
	icons/22/nm-stage02-connecting03.png \
	icons/22/nm-stage02-connecting04.png \
	icons/22/nm-stage02-connecting05.png \
	icons/22/nm-stage02-connecting06.png \
	icons/22/nm-stage02-connecting07.png \
	icons/22/nm-stage02-connecting08.png \
	icons/22/nm-stage02-connecting09.png \
	icons/22/nm-stage02-connecting10.png \
	icons/22/nm-stage02-connecting11.png \
	icons/22/nm-stage03-connecting01.png \
	icons/22/nm-stage03-connecting02.png \
	icons/22/nm-stage03-connecting03.png \
	icons/22/nm-stage03-connecting04.png \
	icons/22/nm-stage03-connecting05.png \
	icons/22/nm-stage03-connecting06.png \
	icons/22/nm-stage03-connecting07.png \
	icons/22/nm-stage03-connecting08.png \
	icons/22/nm-stage03-connecting09.png \
	icons/22/nm-stage03-connecting10.png \
	icons/22/nm-stage03-connecting11.png \
	icons/22/nm-tech-3g.png \
	icons/22/nm-tech-cdma-1x.png \
	icons/22/nm-tech-edge.png \
	icons/22/nm-tech-evdo.png \
	icons/22/nm-tech-gprs.png \
	icons/22/nm-tech-hspa.png \
	icons/22/nm-tech-lte.png \
	icons/22/nm-tech-umts.png \
	icons/22/nm-vpn-active-lock.png \
	icons/22/nm-vpn-connecting01.png \
	icons/22/nm-vpn-connecting02.png \
	icons/22/nm-vpn-connecting03.png \
	icons/22/nm-vpn-connecting04.png \
	icons/22/nm-vpn-connecting05.png \
	icons/22/nm-vpn-connecting06.png \
	icons/22/nm-vpn-connecting07.png \
	icons/22/nm-vpn-connecting08.png \
	icons/22/nm-vpn-connecting09.png \
	icons/22/nm-vpn-connecting10.png \
	icons/22/nm-vpn-connecting11.png \
	icons/22/nm-vpn-connecting12.png \
	icons/22/nm-vpn-connecting13.png \
	icons/22/nm-vpn-connecting14.png \
	icons/22/nm-wwan-tower.png
EXTRA_DIST += $(icon22_DATA)

icon32dir = $(datadir)/icons/hicolor/32x32/apps
icon32_DATA = \
	icons/32/nm-device-wired.png \
	icons/32/nm-no-connection.png
EXTRA_DIST += $(icon32_DATA)

icon48dir = $(datadir)/icons/hicolor/48x48/apps
icon48_DATA = \
	icons/48/nm-device-wireless.png
EXTRA_DIST += $(icon48_DATA)

iconscalabledir=$(datadir)/icons/hicolor/scalable/apps
iconscalable_DATA = \
	icons/scalable/nm-device-wired.svg \
	icons/scalable/nm-no-connection.svg
EXTRA_DIST += $(iconscalable_DATA)

EXTRA_DIST += icons/meson.build

###############################################################################

shared_files = \
	shared/nm-utils/nm-shared-utils.c \
	shared/nm-utils/nm-shared-utils.h \
	$(NULL)

noinst_LTLIBRARIES += src/utils/libutils-libnm.la

src_utils_libutils_libnm_la_CPPFLAGS = \
	$(dflt_cppflags) \
	"-I$(srcdir)/shared" \
	$(GTK3_CFLAGS) \
	$(LIBNM_CFLAGS)

src_utils_libutils_libnm_la_SOURCES = \
	$(shared_files) \
	src/utils/utils.c \
	src/utils/utils.h

src_utils_libutils_libnm_la_LIBADD = \
	$(GTK3_LIBS) \
	$(LIBNM_LIBS)

check_programs += src/utils/tests/test-utils

src_utils_tests_test_utils_SOURCES = src/utils/tests/test-utils.c

src_utils_tests_test_utils_CPPFLAGS = \
	$(dflt_cppflags) \
	"-I$(srcdir)/shared/" \
	"-I$(srcdir)/src/utils" \
	$(GTK3_CFLAGS) \
	$(LIBNM_CFLAGS)

src_utils_tests_test_utils_LDADD = \
	src/utils/libutils-libnm.la \
	$(GTK3_LIBS) \
	$(LIBNM_LIBS)

EXTRA_DIST += src/utils/meson.build

###############################################################################

src/wireless-security/ws-resources.h: src/wireless-security/ws.gresource.xml
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) $< --target=$@ --sourcedir=$(srcdir)/src/wireless-security --generate-header --internal

src/wireless-security/ws-resources.c: src/wireless-security/ws.gresource.xml $(shell $(GLIB_COMPILE_RESOURCES) --sourcedir=$(srcdir)/src/wireless-security --generate-dependencies $(srcdir)/src/wireless-security/ws.gresource.xml)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) $< --target=$@ --sourcedir=$(srcdir)/src/wireless-security --generate-source --internal

CLEANFILES += \
	$(wireless_security_h_gen) \
	$(wireless_security_c_gen)

wireless_security_h_gen = \
	src/wireless-security/ws-resources.h

wireless_security_c_gen = \
	src/wireless-security/ws-resources.c

wireless_security_c_real = \
	src/wireless-security/wireless-security.h \
	src/wireless-security/wireless-security.c \
	src/wireless-security/ws-sae.h \
	src/wireless-security/ws-sae.c \
	src/wireless-security/ws-wep-key.h \
	src/wireless-security/ws-wep-key.c \
	src/wireless-security/ws-wpa-psk.h \
	src/wireless-security/ws-wpa-psk.c \
	src/wireless-security/ws-leap.h \
	src/wireless-security/ws-leap.c \
	src/wireless-security/ws-wpa-eap.h \
	src/wireless-security/ws-wpa-eap.c \
	src/wireless-security/ws-dynamic-wep.h \
	src/wireless-security/ws-dynamic-wep.c \
	src/wireless-security/eap-method.h \
	src/wireless-security/eap-method.c \
	src/wireless-security/eap-method-tls.h \
	src/wireless-security/eap-method-tls.c \
	src/wireless-security/eap-method-leap.h \
	src/wireless-security/eap-method-leap.c \
	src/wireless-security/eap-method-fast.h \
	src/wireless-security/eap-method-fast.c \
	src/wireless-security/eap-method-ttls.h \
	src/wireless-security/eap-method-ttls.c \
	src/wireless-security/eap-method-peap.h \
	src/wireless-security/eap-method-peap.c \
	src/wireless-security/eap-method-simple.h \
	src/wireless-security/eap-method-simple.c \
	src/wireless-security/helpers.h \
	src/wireless-security/helpers.c


noinst_LTLIBRARIES += src/wireless-security/libwireless-security-libnm.la

src_wireless_security_libwireless_security_libnm_la_SOURCES = \
	$(wireless_security_c_real)

nodist_src_wireless_security_libwireless_security_libnm_la_SOURCES = \
	$(wireless_security_c_gen)

src_wireless_security_libwireless_security_libnm_la_CPPFLAGS = \
	$(dflt_cppflags) \
	"-I$(srcdir)/shared" \
	"-I$(srcdir)/src/utils" \
	$(GTK3_CFLAGS) \
	$(LIBNMA_CFLAGS) \
	$(LIBNM_CFLAGS)

src_wireless_security_libwireless_security_libnm_la_LIBADD = \
	src/utils/libutils-libnm.la \
	$(GTK3_LIBS) \
	$(LIBNM_LIBS)

$(src_wireless_security_libwireless_security_libnm_la_OBJECTS): $(wireless_security_h_gen)

EXTRA_DIST += \
	src/wireless-security/eap-method-fast.ui \
	src/wireless-security/eap-method-leap.ui \
	src/wireless-security/eap-method-peap.ui \
	src/wireless-security/eap-method-simple.ui \
	src/wireless-security/eap-method-tls.ui \
	src/wireless-security/eap-method-ttls.ui \
	src/wireless-security/ws-dynamic-wep.ui \
	src/wireless-security/ws-leap.ui \
	src/wireless-security/ws-sae.ui \
	src/wireless-security/ws-wep-key.ui \
	src/wireless-security/ws-wpa-eap.ui \
	src/wireless-security/ws-wpa-psk.ui \
	src/wireless-security/ws.gresource.xml \
	src/wireless-security/meson.build

###############################################################################

src/connection-editor/ce-resources.h: src/connection-editor/ce.gresource.xml
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) $< --target=$@ --sourcedir=$(srcdir)/src/connection-editor --generate-header --internal

src/connection-editor/ce-resources.c: src/connection-editor/ce.gresource.xml $(shell $(GLIB_COMPILE_RESOURCES) --sourcedir=$(srcdir)/src/connection-editor --generate-dependencies $(srcdir)/src/connection-editor/ce.gresource.xml)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) $< --target=$@ --sourcedir=$(srcdir)/src/connection-editor --generate-source --internal

CLEANFILES += \
	$(connection_editor_h_gen) \
	$(connection_editor_c_gen)

connection_editor_h_gen = \
	src/connection-editor/ce-resources.h

connection_editor_c_gen = \
	src/connection-editor/ce-resources.c

connection_editor_hc_real = \
	src/connection-editor/nm-connection-editor.c \
	src/connection-editor/nm-connection-editor.h \
	src/connection-editor/nm-connection-list.c \
	src/connection-editor/nm-connection-list.h \
	src/connection-editor/main.c \
	src/connection-editor/ce-page.h \
	src/connection-editor/ce-page.c \
	src/connection-editor/page-general.h \
	src/connection-editor/page-general.c \
	src/connection-editor/page-ethernet.h \
	src/connection-editor/page-ethernet.c \
	src/connection-editor/page-8021x-security.h \
	src/connection-editor/page-8021x-security.c \
	src/connection-editor/page-wifi.h \
	src/connection-editor/page-wifi.c \
	src/connection-editor/page-wifi-security.h \
	src/connection-editor/page-wifi-security.c \
	src/connection-editor/page-infiniband.h \
	src/connection-editor/page-infiniband.c \
	src/connection-editor/page-ip-tunnel.h \
	src/connection-editor/page-ip-tunnel.c \
	src/connection-editor/page-ip4.h \
	src/connection-editor/page-ip4.c \
	src/connection-editor/page-ip6.h \
	src/connection-editor/page-ip6.c \
	src/connection-editor/page-dsl.h \
	src/connection-editor/page-dsl.c \
	src/connection-editor/page-macsec.h \
	src/connection-editor/page-macsec.c \
	src/connection-editor/page-mobile.h \
	src/connection-editor/page-mobile.c \
	src/connection-editor/page-bluetooth.h \
	src/connection-editor/page-bluetooth.c \
	src/connection-editor/page-ppp.h \
	src/connection-editor/page-ppp.c \
	src/connection-editor/page-proxy.h \
	src/connection-editor/page-proxy.c \
	src/connection-editor/page-vpn.h \
	src/connection-editor/page-vpn.c \
	src/connection-editor/page-master.h \
	src/connection-editor/page-master.c \
	src/connection-editor/page-bond.h \
	src/connection-editor/page-bond.c \
	src/connection-editor/page-team.h \
	src/connection-editor/page-team.c \
	src/connection-editor/page-team-port.h \
	src/connection-editor/page-team-port.c \
	src/connection-editor/page-bridge.h \
	src/connection-editor/page-bridge.c \
	src/connection-editor/page-bridge-port.h \
	src/connection-editor/page-bridge-port.c \
	src/connection-editor/page-vlan.h \
	src/connection-editor/page-vlan.c \
	src/connection-editor/page-dcb.c \
	src/connection-editor/page-dcb.h \
	src/connection-editor/page-wireguard.h \
	src/connection-editor/page-wireguard.c \
	src/connection-editor/vpn-helpers.h \
	src/connection-editor/vpn-helpers.c \
	src/connection-editor/ip4-routes-dialog.h \
	src/connection-editor/ip4-routes-dialog.c \
	src/connection-editor/ip6-routes-dialog.h \
	src/connection-editor/ip6-routes-dialog.c \
	src/connection-editor/ppp-auth-methods-dialog.c \
	src/connection-editor/ppp-auth-methods-dialog.h \
	src/connection-editor/ce-polkit-button.c \
	src/connection-editor/ce-polkit-button.h \
	src/connection-editor/ce-polkit.c \
	src/connection-editor/ce-polkit.h \
	src/connection-editor/ce-utils.c \
	src/connection-editor/ce-utils.h \
	src/connection-editor/connection-helpers.c \
	src/connection-editor/connection-helpers.h

bin_PROGRAMS += src/connection-editor/nm-connection-editor

src_connection_editor_nm_connection_editor_SOURCES = \
	$(connection_editor_hc_real)

nodist_src_connection_editor_nm_connection_editor_SOURCES = \
	$(connection_editor_c_gen)

src_connection_editor_nm_connection_editor_CPPFLAGS = \
	$(dflt_cppflags) \
	-DICONDIR=\""$(datadir)/icons"\" \
	-DBINDIR=\""$(bindir)"\" \
	-DSYSCONFDIR=\""$(sysconfdir)"\" \
	-DLIBDIR=\""$(libdir)"\" \
	-DDATADIR=\""$(datadir)"\" \
	-DNMALOCALEDIR=\"$(datadir)/locale\" \
	"-I$(srcdir)/shared" \
	"-I$(srcdir)/src/utils" \
	"-I$(srcdir)/src/wireless-security" \
	$(GTK3_CFLAGS) \
	$(LIBNMA_CFLAGS) \
	$(LIBNM_CFLAGS) \
	$(JANSSON_CFLAGS) \
	$(SELINUX_CFLAGS)

src_connection_editor_nm_connection_editor_LDADD = \
	src/wireless-security/libwireless-security-libnm.la \
	$(GTK3_LIBS) \
	$(LIBNM_LIBS) \
	$(LIBNMA_LIBS) \
	$(JANSSON_LIBS) \
	$(SELINUX_LIBS) \
	-lm

$(src_connection_editor_nm_connection_editor_OBJECTS): $(connection_editor_h_gen)

EXTRA_src_connection_editor_nm_connection_editor_DEPENDENCIES = linker-script-binary.ver

src_connection_editor_nm_connection_editor_LDFLAGS = \
	-Wl,--version-script="$(srcdir)/linker-script-binary.ver"


EXTRA_DIST += \
	src/connection-editor/ce-ip4-routes.ui \
	src/connection-editor/ce-ip6-routes.ui \
	src/connection-editor/ce-new-connection.ui \
	src/connection-editor/ce-page-bluetooth.ui \
	src/connection-editor/ce-page-bond.ui \
	src/connection-editor/ce-page-bridge-port.ui \
	src/connection-editor/ce-page-bridge.ui \
	src/connection-editor/ce-page-dcb.ui \
	src/connection-editor/ce-page-dsl.ui \
	src/connection-editor/ce-page-ethernet.ui \
	src/connection-editor/ce-page-general.ui \
	src/connection-editor/ce-page-infiniband.ui \
	src/connection-editor/ce-page-ip4.ui \
	src/connection-editor/ce-page-ip6.ui \
	src/connection-editor/ce-page-ip-tunnel.ui \
	src/connection-editor/ce-page-macsec.ui \
	src/connection-editor/ce-page-mobile.ui \
	src/connection-editor/ce-page-ppp.ui \
	src/connection-editor/ce-page-proxy.ui \
	src/connection-editor/ce-page-team-port.ui \
	src/connection-editor/ce-page-team.ui \
	src/connection-editor/ce-page-vlan.ui \
	src/connection-editor/ce-page-wifi-security.ui \
	src/connection-editor/ce-page-wifi.ui \
	src/connection-editor/ce-page-wireguard.ui \
	src/connection-editor/ce-ppp-auth-methods.ui \
	src/connection-editor/gtk/menus.ui \
	src/connection-editor/nm-connection-editor.ui \
	src/connection-editor/nm-connection-list.ui \
	src/connection-editor/ce.gresource.xml \
	src/connection-editor/meson.build

###############################################################################

src/applet-resources.h: src/applet.gresource.xml
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) $< --target=$@ --sourcedir=$(srcdir)/src --generate-header --internal

src/applet-resources.c: src/applet.gresource.xml $(shell $(GLIB_COMPILE_RESOURCES) --sourcedir=$(srcdir)/src --generate-dependencies $(srcdir)/src/applet.gresource.xml)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) $< --target=$@ --sourcedir=$(srcdir)/src --generate-source --internal

CLEANFILES += \
	$(nm_applet_h_gen) \
	$(nm_applet_c_gen)

nm_applet_h_gen = \
	src/applet-resources.h

nm_applet_c_gen = \
	src/applet-resources.c

nm_applet_hc_real = \
	shared/nm-utils/nm-compat.c \
	src/main.c \
	src/applet.c \
	src/applet.h \
	src/applet-agent.c \
	src/applet-agent.h \
	src/applet-vpn-request.c \
	src/applet-vpn-request.h \
	src/ethernet-dialog.h \
	src/ethernet-dialog.c \
	src/applet-dialogs.h \
	src/applet-dialogs.c \
	src/applet-device-ethernet.h \
	src/applet-device-ethernet.c \
	src/applet-device-wifi.h \
	src/applet-device-wifi.c \
	src/ap-menu-item.h \
	src/ap-menu-item.c \
	src/mb-menu-item.h \
	src/mb-menu-item.c \
	src/mobile-helpers.c \
	src/mobile-helpers.h \
	src/applet-device-bt.h \
	src/applet-device-bt.c \
	src/fallback-icon.h

if WITH_WWAN
nm_applet_hc_real += \
	src/applet-device-broadband.h \
	src/applet-device-broadband.c
endif

bin_PROGRAMS += src/nm-applet

src_nm_applet_SOURCES = \
	$(nm_applet_hc_real)

nodist_src_nm_applet_SOURCES = \
	$(nm_applet_c_gen)

src_nm_applet_CPPFLAGS = \
	$(dflt_cppflags) \
	-DICONDIR=\""$(datadir)/icons"\" \
	-DBINDIR=\""$(bindir)"\" \
	-DSYSCONFDIR=\""$(sysconfdir)"\" \
	-DLIBEXECDIR=\""$(libexecdir)"\" \
	-DAUTOSTARTDIR=\""$(sysconfdir)/xdg/autostart"\" \
	-DNMALOCALEDIR=\"$(datadir)/locale\" \
	-DG_LOG_DOMAIN=\""nm-applet"\" \
	"-I$(srcdir)/shared" \
	"-I$(srcdir)/src/utils" \
	"-I$(srcdir)/src/wireless-security" \
	$(GTK3_CFLAGS) \
	$(LIBNMA_CFLAGS) \
	$(LIBNM_CFLAGS) \
	$(LIBSECRET_CFLAGS) \
	$(NOTIFY_CFLAGS) \
	$(MM_GLIB_CFLAGS) \
	$(APPINDICATOR_CFLAGS)

src_nm_applet_LDADD = \
	src/wireless-security/libwireless-security-libnm.la \
	$(GTK3_LIBS) \
	$(LIBNM_LIBS) \
	$(LIBNMA_LIBS) \
	$(LIBSECRET_LIBS) \
	$(NOTIFY_LIBS) \
	$(MM_GLIB_LIBS) \
	$(APPINDICATOR_LIBS) \
	-lm

$(src_nm_applet_OBJECTS): $(nm_applet_h_gen)

EXTRA_src_nm_applet_DEPENDENCIES = linker-script-binary.ver

src_nm_applet_LDFLAGS = \
	-Wl,--version-script="$(srcdir)/linker-script-binary.ver"


EXTRA_DIST += \
	src/8021x.ui \
	src/gsm-unlock.ui \
	src/info.ui \
	src/applet.gresource.xml \
	src/meson.build

###############################################################################

EXTRA_DIST += \
	shared/nm-utils/gsystem-local-alloc.h \
	shared/nm-utils/nm-compat.c \
	shared/nm-utils/nm-compat.h \
	shared/nm-utils/nm-glib.h \
	shared/nm-utils/nm-macros-internal.h \
	shared/nm-utils/nm-shared-utils.c \
	shared/nm-utils/nm-shared-utils.h \
	shared/nm-utils/nm-test-utils.h \
	shared/nm-utils/nm-vpn-editor-plugin-call.h \
	shared/nm-default.h \
	shared/nm-libnm-compat.h \
	shared/meson.build \
	$(NULL)

###############################################################################

man_MANS += \
	man/nm-applet.1 \
	man/nm-connection-editor.1

EXTRA_DIST += man/meson.build

###############################################################################

check_PROGRAMS += $(check_programs)

check-local: $(check_local)

TESTS += $(check_programs)

EXTRA_DIST += \
	linker-script-binary.ver \
	CONTRIBUTING \
	Makefile.glib \
	autogen.sh \
	meson.build \
	meson_options.txt \
	meson_post_install.py \
	config.h.meson \
	\
	po/meson.build


autostartdir = $(sysconfdir)/xdg/autostart
autostart_in_files = nm-applet.desktop.in
autostart_DATA = $(autostart_in_files:.desktop.in=.desktop)

nm-applet.desktop: nm-applet.desktop.in
	$(AM_V_GEN)$(MSGFMT) --desktop --template $< -d $(top_srcdir)/po -o $@

applicationsdir = $(datadir)/applications
applications_DATA = $(autostart_DATA)

desktopdir = $(datadir)/applications
desktop_in_files = nm-connection-editor.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)

nm-connection-editor.desktop: nm-connection-editor.desktop.in
	$(AM_V_GEN)$(MSGFMT) --desktop --template $< -d $(top_srcdir)/po -o $@

appdatadir = $(datadir)/metainfo
appdata_DATA = $(appdata_in_files:.xml.in=.xml)
appdata_in_files = nm-connection-editor.appdata.xml.in

nm-connection-editor.appdata.xml: nm-connection-editor.appdata.xml.in
	$(AM_V_GEN)$(MSGFMT) --xml --template $< -d $(top_srcdir)/po -o $@

convertdir=$(datadir)/GConf/gsettings
convert_DATA=nm-applet.convert

EXTRA_DIST += \
	$(convert_DATA) \
	$(appdata_in_files) \
	$(autostart_in_files) \
	$(desktop_in_files)

CLEANFILES += \
	$(typelib_DATA) \
	\
	$(autostart_DATA) \
	$(desktop_DATA) \
	$(appdata_DATA) \
	$(BUILT_SOURCES)
