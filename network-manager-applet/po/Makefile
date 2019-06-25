# Makefile for program source directory in GNU NLS utilities package.
# Copyright (C) 1995, 1996, 1997 by Ulrich Drepper <drepper@gnu.ai.mit.edu>
# Copyright (C) 2004-2008 Rodney Dawes <dobey.pwns@gmail.com>
#
# This file may be copied and used freely without restrictions.  It may
# be used in projects which are not available under a GNU Public License,
# but which still want to provide support for the GNU gettext functionality.
#
# - Modified by Owen Taylor <otaylor@redhat.com> to use GETTEXT_PACKAGE
#   instead of PACKAGE and to look for po2tbl in ./ not in intl/
#
# - Modified by jacob berkman <jacob@ximian.com> to install
#   Makefile.in.in and po2tbl.sed.in for use with glib-gettextize
#
# - Modified by Rodney Dawes <dobey.pwns@gmail.com> for use with intltool
#
# We have the following line for use by intltoolize:
# INTLTOOL_MAKEFILE

GETTEXT_PACKAGE = nm-applet
PACKAGE = network-manager-applet
VERSION = 1.8.20

SHELL = /bin/bash

srcdir = .
top_srcdir = ..
top_builddir = ..


prefix = /usr
exec_prefix = ${prefix}
datadir = ${datarootdir}
datarootdir = ${prefix}/share
libdir = ${prefix}/lib/x86_64-linux-gnu
localedir = ${datarootdir}/locale
subdir = po
install_sh = ${SHELL} /workdir/network-manager-applet/install-sh
# Automake >= 1.8 provides $(MKDIR_P).
# Until it can be supposed, use the safe fallback:
mkdir_p = $(install_sh) -d

INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644

GMSGFMT = /usr/bin/msgfmt
MSGFMT = /usr/bin/msgfmt
XGETTEXT = /usr/bin/xgettext
INTLTOOL_UPDATE = /usr/bin/intltool-update
INTLTOOL_EXTRACT = /usr/bin/intltool-extract
MSGMERGE = INTLTOOL_EXTRACT="$(INTLTOOL_EXTRACT)" XGETTEXT="$(XGETTEXT)" srcdir=$(srcdir) $(INTLTOOL_UPDATE) --gettext-package $(GETTEXT_PACKAGE) --dist
GENPOT   = INTLTOOL_EXTRACT="$(INTLTOOL_EXTRACT)" XGETTEXT="$(XGETTEXT)" srcdir=$(srcdir) $(INTLTOOL_UPDATE) --gettext-package $(GETTEXT_PACKAGE) --pot

ALL_LINGUAS = 

PO_LINGUAS=$(shell if test -r $(srcdir)/LINGUAS; then grep -v "^\#" $(srcdir)/LINGUAS; else echo "$(ALL_LINGUAS)"; fi)

USER_LINGUAS=$(shell if test -n "$(LINGUAS)"; then LLINGUAS="$(LINGUAS)"; ALINGUAS="$(ALL_LINGUAS)"; for lang in $$LLINGUAS; do if test -n "`grep \^$$lang$$ $(srcdir)/LINGUAS 2>/dev/null`" -o -n "`echo $$ALINGUAS|tr ' ' '\n'|grep \^$$lang$$`"; then printf "$$lang "; fi; done; fi)

USE_LINGUAS=$(shell if test -n "$(USER_LINGUAS)" -o -n "$(LINGUAS)"; then LLINGUAS="$(USER_LINGUAS)"; else if test -n "$(PO_LINGUAS)"; then LLINGUAS="$(PO_LINGUAS)"; else LLINGUAS="$(ALL_LINGUAS)"; fi; fi; for lang in $$LLINGUAS; do printf "$$lang "; done)

POFILES=$(shell LINGUAS="$(PO_LINGUAS)"; for lang in $$LINGUAS; do printf "$$lang.po "; done)

DISTFILES = Makefile.in.in POTFILES.in $(POFILES)
EXTRA_DISTFILES = ChangeLog POTFILES.skip Makevars LINGUAS

POTFILES = \
	../nm-applet.desktop.in \
	../nm-connection-editor.desktop.in \
	../org.gnome.nm-applet.gschema.xml.in \
	../nm-connection-editor.appdata.xml.in \
	../shared/nm-utils/nm-shared-utils.c \
	../src/8021x.ui \
	../src/ap-menu-item.c \
	../src/applet.c \
	../src/applet-device-broadband.c \
	../src/applet-device-bt.c \
	../src/applet-device-ethernet.c \
	../src/applet-device-wifi.c \
	../src/applet-dialogs.c \
	../src/applet-vpn-request.c \
	../src/applet.h \
	../src/connection-editor/ce-ip4-routes.ui \
	../src/connection-editor/ce-ip6-routes.ui \
	../src/connection-editor/ce-new-connection.ui \
	../src/connection-editor/ce-page-bluetooth.ui \
	../src/connection-editor/ce-page-bond.ui \
	../src/connection-editor/ce-page-bridge-port.ui \
	../src/connection-editor/ce-page-bridge.ui \
	../src/connection-editor/ce-page.c \
	../src/connection-editor/ce-page-dcb.ui \
	../src/connection-editor/ce-page-dsl.ui \
	../src/connection-editor/ce-page-ethernet.ui \
	../src/connection-editor/ce-page-general.ui \
	../src/connection-editor/ce-page.h \
	../src/connection-editor/ce-page-infiniband.ui \
	../src/connection-editor/ce-page-ip-tunnel.ui \
	../src/connection-editor/ce-page-ip4.ui \
	../src/connection-editor/ce-page-ip6.ui \
	../src/connection-editor/ce-page-macsec.ui \
	../src/connection-editor/ce-page-mobile.ui \
	../src/connection-editor/ce-page-ppp.ui \
	../src/connection-editor/ce-page-proxy.ui \
	../src/connection-editor/ce-page-team-port.ui \
	../src/connection-editor/ce-page-team.ui \
	../src/connection-editor/ce-page-vlan.ui \
	../src/connection-editor/ce-page-wifi-security.ui \
	../src/connection-editor/ce-page-wifi.ui \
	../src/connection-editor/ce-polkit.c \
	../src/connection-editor/ce-polkit-button.c \
	../src/connection-editor/ce-ppp-auth-methods.ui \
	../src/connection-editor/connection-helpers.c \
	../src/connection-editor/gtk/menus.ui \
	../src/connection-editor/ip4-routes-dialog.c \
	../src/connection-editor/ip6-routes-dialog.c \
	../src/connection-editor/nm-connection-editor.c \
	../src/connection-editor/nm-connection-editor.ui \
	../src/connection-editor/nm-connection-list.c \
	../src/connection-editor/nm-connection-list.ui \
	../src/connection-editor/page-8021x-security.c \
	../src/connection-editor/page-bluetooth.c \
	../src/connection-editor/page-bond.c \
	../src/connection-editor/page-bridge.c \
	../src/connection-editor/page-bridge-port.c \
	../src/connection-editor/page-dcb.c \
	../src/connection-editor/page-dsl.c \
	../src/connection-editor/page-ethernet.c \
	../src/connection-editor/page-general.c \
	../src/connection-editor/page-infiniband.c \
	../src/connection-editor/page-ip-tunnel.c \
	../src/connection-editor/page-ip4.c \
	../src/connection-editor/page-ip6.c \
	../src/connection-editor/page-macsec.c \
	../src/connection-editor/page-master.c \
	../src/connection-editor/page-mobile.c \
	../src/connection-editor/page-ppp.c \
	../src/connection-editor/page-proxy.c \
	../src/connection-editor/page-team.c \
	../src/connection-editor/page-team-port.c \
	../src/connection-editor/page-vlan.c \
	../src/connection-editor/page-vpn.c \
	../src/connection-editor/page-wifi.c \
	../src/connection-editor/page-wifi-security.c \
	../src/connection-editor/vpn-helpers.c \
	../src/ethernet-dialog.c \
	../src/gsm-unlock.ui \
	../src/info.ui \
	../src/libnma/nma-file-cert-chooser.c \
	../src/libnma/nma-mobile-providers.c \
	../src/libnma/nma-mobile-wizard.c \
	../src/libnma/nma-mobile-wizard.ui \
	../src/libnma/nma-cert-chooser-button.c \
	../src/libnma/nma-pkcs11-cert-chooser.c \
	../src/libnma/nma-pkcs11-cert-chooser-dialog.c \
	../src/libnma/nma-pkcs11-cert-chooser-dialog.ui \
	../src/libnma/nma-pkcs11-token-login-dialog.c \
	../src/libnma/nma-pkcs11-token-login-dialog.ui \
	../src/libnma/nma-ui-utils.c \
	../src/libnma/nma-vpn-password-dialog.c \
	../src/libnma/nma-vpn-password-dialog.ui \
	../src/libnma/nma-wifi-dialog.c \
	../src/libnma/wifi.ui \
	../src/libnm-gtk/nm-mobile-providers.c \
	../src/libnm-gtk/nm-mobile-wizard.c \
	../src/libnm-gtk/nm-ui-utils.c \
	../src/libnm-gtk/nm-vpn-password-dialog.c \
	../src/libnm-gtk/nm-wifi-dialog.c \
	../src/libnm-gtk/tests/test-mobile-providers.c \
	../src/libnm-gtk/wifi.ui \
	../src/main.c \
	../src/mb-menu-item.c \
	../src/mobile-helpers.c \
	../src/utils/utils.c \
	../src/wireless-security/eap-method.c \
	../src/wireless-security/eap-method-fast.c \
	../src/wireless-security/eap-method-fast.ui \
	../src/wireless-security/eap-method-leap.c \
	../src/wireless-security/eap-method-leap.ui \
	../src/wireless-security/eap-method-peap.c \
	../src/wireless-security/eap-method-peap.ui \
	../src/wireless-security/eap-method-simple.c \
	../src/wireless-security/eap-method-simple.ui \
	../src/wireless-security/eap-method-tls.c \
	../src/wireless-security/eap-method-tls.ui \
	../src/wireless-security/eap-method-ttls.c \
	../src/wireless-security/eap-method-ttls.ui \
	../src/wireless-security/wireless-security.c \
	../src/wireless-security/ws-dynamic-wep.ui \
	../src/wireless-security/ws-leap.c \
	../src/wireless-security/ws-leap.ui \
	../src/wireless-security/ws-wep-key.c \
	../src/wireless-security/ws-wep-key.ui \
	../src/wireless-security/ws-wpa-eap.ui \
	../src/wireless-security/ws-wpa-psk.c \
	../src/wireless-security/ws-wpa-psk.ui

CATALOGS=$(shell LINGUAS="$(USE_LINGUAS)"; for lang in $$LINGUAS; do printf "$$lang.gmo "; done)

.SUFFIXES:
.SUFFIXES: .po .pox .gmo .mo .msg .cat

AM_DEFAULT_VERBOSITY = 1
INTLTOOL_V_MSGFMT = $(INTLTOOL__v_MSGFMT_$(V))
INTLTOOL__v_MSGFMT_= $(INTLTOOL__v_MSGFMT_$(AM_DEFAULT_VERBOSITY))
INTLTOOL__v_MSGFMT_0 = @echo "  MSGFMT" $@;

.po.pox:
	$(MAKE) $(GETTEXT_PACKAGE).pot
	$(MSGMERGE) $* $(GETTEXT_PACKAGE).pot -o $*.pox

.po.mo:
	$(INTLTOOL_V_MSGFMT)$(MSGFMT) -o $@ $<

.po.gmo:
	$(INTLTOOL_V_MSGFMT)file=`echo $* | sed 's,.*/,,'`.gmo \
	  && rm -f $$file && $(GMSGFMT) -o $$file $<

.po.cat:
	sed -f ../intl/po2msg.sed < $< > $*.msg \
	  && rm -f $@ && gencat $@ $*.msg


all: all-yes

all-yes: $(CATALOGS)
all-no:

$(GETTEXT_PACKAGE).pot: $(POTFILES)
	$(GENPOT)

install: install-data
install-data: install-data-yes
install-data-no: all
install-data-yes: all
	linguas="$(USE_LINGUAS)"; \
	for lang in $$linguas; do \
	  dir=$(DESTDIR)$(localedir)/$$lang/LC_MESSAGES; \
	  $(mkdir_p) $$dir; \
	  if test -r $$lang.gmo; then \
	    $(INSTALL_DATA) $$lang.gmo $$dir/$(GETTEXT_PACKAGE).mo; \
	    echo "installing $$lang.gmo as $$dir/$(GETTEXT_PACKAGE).mo"; \
	  else \
	    $(INSTALL_DATA) $(srcdir)/$$lang.gmo $$dir/$(GETTEXT_PACKAGE).mo; \
	    echo "installing $(srcdir)/$$lang.gmo as" \
		 "$$dir/$(GETTEXT_PACKAGE).mo"; \
	  fi; \
	  if test -r $$lang.gmo.m; then \
	    $(INSTALL_DATA) $$lang.gmo.m $$dir/$(GETTEXT_PACKAGE).mo.m; \
	    echo "installing $$lang.gmo.m as $$dir/$(GETTEXT_PACKAGE).mo.m"; \
	  else \
	    if test -r $(srcdir)/$$lang.gmo.m ; then \
	      $(INSTALL_DATA) $(srcdir)/$$lang.gmo.m \
		$$dir/$(GETTEXT_PACKAGE).mo.m; \
	      echo "installing $(srcdir)/$$lang.gmo.m as" \
		   "$$dir/$(GETTEXT_PACKAGE).mo.m"; \
	    else \
	      true; \
	    fi; \
	  fi; \
	done

# Empty stubs to satisfy archaic automake needs
dvi info ctags tags CTAGS TAGS ID:

# Define this as empty until I found a useful application.
install-exec installcheck:

uninstall:
	linguas="$(USE_LINGUAS)"; \
	for lang in $$linguas; do \
	  rm -f $(DESTDIR)$(localedir)/$$lang/LC_MESSAGES/$(GETTEXT_PACKAGE).mo; \
	  rm -f $(DESTDIR)$(localedir)/$$lang/LC_MESSAGES/$(GETTEXT_PACKAGE).mo.m; \
	done

check: all $(GETTEXT_PACKAGE).pot
	rm -f missing notexist
	srcdir=$(srcdir) $(INTLTOOL_UPDATE) -m
	if [ -r missing -o -r notexist ]; then \
	  exit 1; \
	fi

mostlyclean:
	rm -f *.pox $(GETTEXT_PACKAGE).pot *.old.po cat-id-tbl.tmp
	rm -f .intltool-merge-cache

clean: mostlyclean

distclean: clean
	rm -f Makefile Makefile.in POTFILES stamp-it
	rm -f *.mo *.msg *.cat *.cat.m *.gmo

maintainer-clean: distclean
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."
	rm -f Makefile.in.in

distdir = ../$(PACKAGE)-$(VERSION)/$(subdir)
dist distdir: $(DISTFILES)
	dists="$(DISTFILES)"; \
	extra_dists="$(EXTRA_DISTFILES)"; \
	for file in $$extra_dists; do \
	  test -f $(srcdir)/$$file && dists="$$dists $(srcdir)/$$file"; \
	done; \
	for file in $$dists; do \
	  test -f $$file || file="$(srcdir)/$$file"; \
	  ln $$file $(distdir) 2> /dev/null \
	    || cp -p $$file $(distdir); \
	done

update-po: Makefile
	$(MAKE) $(GETTEXT_PACKAGE).pot
	tmpdir=`pwd`; \
	linguas="$(USE_LINGUAS)"; \
	for lang in $$linguas; do \
	  echo "$$lang:"; \
	  result="`$(MSGMERGE) -o $$tmpdir/$$lang.new.po $$lang`"; \
	  if $$result; then \
	    if cmp $(srcdir)/$$lang.po $$tmpdir/$$lang.new.po >/dev/null 2>&1; then \
	      rm -f $$tmpdir/$$lang.new.po; \
            else \
	      if mv -f $$tmpdir/$$lang.new.po $$lang.po; then \
	        :; \
	      else \
	        echo "msgmerge for $$lang.po failed: cannot move $$tmpdir/$$lang.new.po to $$lang.po" 1>&2; \
	        rm -f $$tmpdir/$$lang.new.po; \
	        exit 1; \
	      fi; \
	    fi; \
	  else \
	    echo "msgmerge for $$lang.gmo failed!"; \
	    rm -f $$tmpdir/$$lang.new.po; \
	  fi; \
	done

Makefile POTFILES: stamp-it
	@if test ! -f $@; then \
	  rm -f stamp-it; \
	  $(MAKE) stamp-it; \
	fi

stamp-it: Makefile.in.in $(top_builddir)/config.status POTFILES.in
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/Makefile.in CONFIG_HEADERS= CONFIG_LINKS= \
	       $(SHELL) ./config.status

# Tell versions [3.59,3.63) of GNU make not to export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
