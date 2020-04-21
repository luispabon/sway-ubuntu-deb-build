# Makefile for PO directory in any package using GNU gettext.
# Copyright (C) 1995-1997, 2000-2007, 2009-2010 by Ulrich Drepper <drepper@gnu.ai.mit.edu>
#
# This file can be copied and used freely without restrictions.  It can
# be used in projects which are not available under the GNU General Public
# License but which still want to provide support for the GNU gettext
# functionality.
# Please note that the actual code of GNU gettext is covered by the GNU
# General Public License and is *not* in the public domain.
#
# Origin: gettext-0.18
GETTEXT_MACRO_VERSION = 0.18

PACKAGE = network-manager-applet
VERSION = 1.8.24
PACKAGE_BUGREPORT = https://gitlab.gnome.org/GNOME/network-manager-applet/issues

SHELL = /bin/sh


srcdir = .
top_srcdir = ..


prefix = /usr
exec_prefix = ${prefix}
datarootdir = ${prefix}/share
datadir = ${datarootdir}
localedir = ${datarootdir}/locale
gettextsrcdir = $(datadir)/gettext/po

INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644

# We use $(mkdir_p).
# In automake <= 1.9.x, $(mkdir_p) is defined either as "mkdir -p --" or as
# "$(mkinstalldirs)" or as "$(install_sh) -d". For these automake versions,
# ${SHELL} /workdir/network-manager-applet/install-sh does not start with $(SHELL), so we add it.
# In automake >= 1.10, /usr/bin/mkdir -p is derived from ${MKDIR_P}, which is defined
# either as "/path/to/mkdir -p" or ".../install-sh -c -d". For these automake
# versions, $(mkinstalldirs) and $(install_sh) are unused.
mkinstalldirs = $(SHELL) ${SHELL} /workdir/network-manager-applet/install-sh -d
install_sh = $(SHELL) ${SHELL} /workdir/network-manager-applet/install-sh
MKDIR_P = /usr/bin/mkdir -p
mkdir_p = /usr/bin/mkdir -p

GMSGFMT_ = /usr/bin/msgfmt
GMSGFMT_no = /usr/bin/msgfmt
GMSGFMT_yes = /usr/bin/msgfmt
GMSGFMT = $(GMSGFMT_$(USE_MSGCTXT))
MSGFMT_ = /usr/bin/msgfmt
MSGFMT_no = /usr/bin/msgfmt
MSGFMT_yes = /usr/bin/msgfmt
MSGFMT = $(MSGFMT_$(USE_MSGCTXT))
XGETTEXT_ = /usr/bin/xgettext
XGETTEXT_no = /usr/bin/xgettext
XGETTEXT_yes = /usr/bin/xgettext
XGETTEXT = $(XGETTEXT_$(USE_MSGCTXT))
MSGMERGE = msgmerge
MSGMERGE_UPDATE = /usr/bin/msgmerge --update
MSGINIT = msginit
MSGCONV = msgconv
MSGFILTER = msgfilter

POFILES =  af.po an.po ar.po as.po ast.po be.po be@latin.po bg.po bn_IN.po bs.po ca.po ca@valencia.po crh.po cs.po da.po de.po dz.po el.po en_CA.po en_GB.po eo.po es.po et.po eu.po fa.po fi.po fr.po gd.po gl.po gu.po he.po hi.po hr.po hu.po id.po is.po it.po ja.po kk.po km.po kn.po ko.po ku.po lt.po lv.po mk.po ml.po mr.po ms.po nb.po ne.po nl.po nn.po oc.po or.po pa.po pl.po pt.po pt_BR.po ro.po ru.po rw.po sk.po sl.po sq.po sr.po sr@latin.po sv.po ta.po te.po tg.po th.po tr.po ug.po uk.po ur.po vi.po wa.po zh_CN.po zh_HK.po zh_TW.po
GMOFILES =  af.gmo an.gmo ar.gmo as.gmo ast.gmo be.gmo be@latin.gmo bg.gmo bn_IN.gmo bs.gmo ca.gmo ca@valencia.gmo crh.gmo cs.gmo da.gmo de.gmo dz.gmo el.gmo en_CA.gmo en_GB.gmo eo.gmo es.gmo et.gmo eu.gmo fa.gmo fi.gmo fr.gmo gd.gmo gl.gmo gu.gmo he.gmo hi.gmo hr.gmo hu.gmo id.gmo is.gmo it.gmo ja.gmo kk.gmo km.gmo kn.gmo ko.gmo ku.gmo lt.gmo lv.gmo mk.gmo ml.gmo mr.gmo ms.gmo nb.gmo ne.gmo nl.gmo nn.gmo oc.gmo or.gmo pa.gmo pl.gmo pt.gmo pt_BR.gmo ro.gmo ru.gmo rw.gmo sk.gmo sl.gmo sq.gmo sr.gmo sr@latin.gmo sv.gmo ta.gmo te.gmo tg.gmo th.gmo tr.gmo ug.gmo uk.gmo ur.gmo vi.gmo wa.gmo zh_CN.gmo zh_HK.gmo zh_TW.gmo
UPDATEPOFILES =  af.po-update an.po-update ar.po-update as.po-update ast.po-update be.po-update be@latin.po-update bg.po-update bn_IN.po-update bs.po-update ca.po-update ca@valencia.po-update crh.po-update cs.po-update da.po-update de.po-update dz.po-update el.po-update en_CA.po-update en_GB.po-update eo.po-update es.po-update et.po-update eu.po-update fa.po-update fi.po-update fr.po-update gd.po-update gl.po-update gu.po-update he.po-update hi.po-update hr.po-update hu.po-update id.po-update is.po-update it.po-update ja.po-update kk.po-update km.po-update kn.po-update ko.po-update ku.po-update lt.po-update lv.po-update mk.po-update ml.po-update mr.po-update ms.po-update nb.po-update ne.po-update nl.po-update nn.po-update oc.po-update or.po-update pa.po-update pl.po-update pt.po-update pt_BR.po-update ro.po-update ru.po-update rw.po-update sk.po-update sl.po-update sq.po-update sr.po-update sr@latin.po-update sv.po-update ta.po-update te.po-update tg.po-update th.po-update tr.po-update ug.po-update uk.po-update ur.po-update vi.po-update wa.po-update zh_CN.po-update zh_HK.po-update zh_TW.po-update
DUMMYPOFILES =  af.nop an.nop ar.nop as.nop ast.nop be.nop be@latin.nop bg.nop bn_IN.nop bs.nop ca.nop ca@valencia.nop crh.nop cs.nop da.nop de.nop dz.nop el.nop en_CA.nop en_GB.nop eo.nop es.nop et.nop eu.nop fa.nop fi.nop fr.nop gd.nop gl.nop gu.nop he.nop hi.nop hr.nop hu.nop id.nop is.nop it.nop ja.nop kk.nop km.nop kn.nop ko.nop ku.nop lt.nop lv.nop mk.nop ml.nop mr.nop ms.nop nb.nop ne.nop nl.nop nn.nop oc.nop or.nop pa.nop pl.nop pt.nop pt_BR.nop ro.nop ru.nop rw.nop sk.nop sl.nop sq.nop sr.nop sr@latin.nop sv.nop ta.nop te.nop tg.nop th.nop tr.nop ug.nop uk.nop ur.nop vi.nop wa.nop zh_CN.nop zh_HK.nop zh_TW.nop
DISTFILES.common = Makefile.in.in remove-potcdate.sin \
$(DISTFILES.common.extra1) $(DISTFILES.common.extra2) $(DISTFILES.common.extra3)
DISTFILES = $(DISTFILES.common) Makevars POTFILES.in \
$(POFILES) $(GMOFILES) \
$(DISTFILES.extra1) $(DISTFILES.extra2) $(DISTFILES.extra3)

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
     ../src/libnma/nma-bar-code-widget.c \
     ../src/libnma/nma-bar-code-widget.ui \
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
     ../src/wireless-security/ws-sae.c \
     ../src/wireless-security/ws-sae.ui \
     ../src/wireless-security/ws-wep-key.c \
     ../src/wireless-security/ws-wep-key.ui \
     ../src/wireless-security/ws-wpa-eap.ui \
     ../src/wireless-security/ws-wpa-psk.c \
     ../src/wireless-security/ws-wpa-psk.ui

CATALOGS =  af.gmo an.gmo ar.gmo as.gmo ast.gmo be.gmo be@latin.gmo bg.gmo bn_IN.gmo bs.gmo ca.gmo ca@valencia.gmo crh.gmo cs.gmo da.gmo de.gmo dz.gmo el.gmo en_CA.gmo en_GB.gmo eo.gmo es.gmo et.gmo eu.gmo fa.gmo fi.gmo fr.gmo gd.gmo gl.gmo gu.gmo he.gmo hi.gmo hr.gmo hu.gmo id.gmo is.gmo it.gmo ja.gmo kk.gmo km.gmo kn.gmo ko.gmo ku.gmo lt.gmo lv.gmo mk.gmo ml.gmo mr.gmo ms.gmo nb.gmo ne.gmo nl.gmo nn.gmo oc.gmo or.gmo pa.gmo pl.gmo pt.gmo pt_BR.gmo ro.gmo ru.gmo rw.gmo sk.gmo sl.gmo sq.gmo sr.gmo sr@latin.gmo sv.gmo ta.gmo te.gmo tg.gmo th.gmo tr.gmo ug.gmo uk.gmo ur.gmo vi.gmo wa.gmo zh_CN.gmo zh_HK.gmo zh_TW.gmo

# Makevars gets inserted here. (Don't remove this line!)
DOMAIN = nm-applet

subdir = po
top_builddir = ..

XGETTEXT_OPTIONS = --from-code=UTF-8 --keyword=_ --keyword=N_ --keyword=C_:1c,2 --keyword=NC_:1c,2 --keyword=g_dngettext:2,3 --add-comments
COPYRIGHT_HOLDER = $(PACKAGE) authors
MSGID_BUGS_ADDRESS = https://gitlab.gnome.org/GNOME/$(PACKAGE)/
EXTRA_LOCALE_CATEGORIES =

.SUFFIXES:
.SUFFIXES: .po .gmo .mo .sed .sin .nop .po-create .po-update

.po.mo:
	@echo "$(MSGFMT) -c -o $@ $<"; \
	$(MSGFMT) -c -o t-$@ $< && mv t-$@ $@

.po.gmo:
	@lang=`echo $* | sed -e 's,.*/,,'`; \
	test "$(srcdir)" = . && cdcmd="" || cdcmd="cd $(srcdir) && "; \
	echo "$${cdcmd}rm -f $${lang}.gmo && $(GMSGFMT) -c --statistics --verbose -o $${lang}.gmo $${lang}.po"; \
	cd $(srcdir) && rm -f $${lang}.gmo && $(GMSGFMT) -c --statistics --verbose -o t-$${lang}.gmo $${lang}.po && mv t-$${lang}.gmo $${lang}.gmo

.sin.sed:
	sed -e '/^#/d' $< > t-$@
	mv t-$@ $@


all: check-macro-version all-yes

all-yes: stamp-po
all-no:

# Ensure that the gettext macros and this Makefile.in.in are in sync.
check-macro-version:
	@test "$(GETTEXT_MACRO_VERSION)" = "0.18" \
	  || { echo "*** error: gettext infrastructure mismatch: using a Makefile.in.in from gettext version $(GETTEXT_MACRO_VERSION) but the autoconf macros are from gettext version 0.18" 1>&2; \
	       exit 1; \
	     }

# $(srcdir)/$(DOMAIN).pot is only created when needed. When xgettext finds no
# internationalized messages, no $(srcdir)/$(DOMAIN).pot is created (because
# we don't want to bother translators with empty POT files). We assume that
# LINGUAS is empty in this case, i.e. $(POFILES) and $(GMOFILES) are empty.
# In this case, stamp-po is a nop (i.e. a phony target).

# stamp-po is a timestamp denoting the last time at which the CATALOGS have
# been loosely updated. Its purpose is that when a developer or translator
# checks out the package via CVS, and the $(DOMAIN).pot file is not in CVS,
# "make" will update the $(DOMAIN).pot and the $(CATALOGS), but subsequent
# invocations of "make" will do nothing. This timestamp would not be necessary
# if updating the $(CATALOGS) would always touch them; however, the rule for
# $(POFILES) has been designed to not touch files that don't need to be
# changed.
stamp-po: $(srcdir)/$(DOMAIN).pot
	test ! -f $(srcdir)/$(DOMAIN).pot || \
	  test -z "$(GMOFILES)" || $(MAKE) $(GMOFILES)
	@test ! -f $(srcdir)/$(DOMAIN).pot || { \
	  echo "touch stamp-po" && \
	  echo timestamp > stamp-poT && \
	  mv stamp-poT stamp-po; \
	}

# Note: Target 'all' must not depend on target '$(DOMAIN).pot-update',
# otherwise packages like GCC can not be built if only parts of the source
# have been downloaded.

# This target rebuilds $(DOMAIN).pot; it is an expensive operation.
# Note that $(DOMAIN).pot is not touched if it doesn't need to be changed.
$(DOMAIN).pot-update: $(POTFILES) $(srcdir)/POTFILES.in remove-potcdate.sed
	if LC_ALL=C grep 'GNU network-manager-applet' $(top_srcdir)/* 2>/dev/null | grep -v 'libtool:' >/dev/null; then \
	  package_gnu='GNU '; \
	else \
	  package_gnu=''; \
	fi; \
	if test -n '$(MSGID_BUGS_ADDRESS)' || test '$(PACKAGE_BUGREPORT)' = '@'PACKAGE_BUGREPORT'@'; then \
	  msgid_bugs_address='$(MSGID_BUGS_ADDRESS)'; \
	else \
	  msgid_bugs_address='$(PACKAGE_BUGREPORT)'; \
	fi; \
	case `$(XGETTEXT) --version | sed 1q | sed -e 's,^[^0-9]*,,'` in \
	  '' | 0.[0-9] | 0.[0-9].* | 0.1[0-5] | 0.1[0-5].* | 0.16 | 0.16.[0-1]*) \
	    $(XGETTEXT) --default-domain=$(DOMAIN) --directory=$(top_srcdir) \
	      --add-comments=TRANSLATORS: $(XGETTEXT_OPTIONS)  \
	      --files-from=$(srcdir)/POTFILES.in \
	      --copyright-holder='$(COPYRIGHT_HOLDER)' \
	      --msgid-bugs-address="$$msgid_bugs_address" \
	    ;; \
	  *) \
	    $(XGETTEXT) --default-domain=$(DOMAIN) --directory=$(top_srcdir) \
	      --add-comments=TRANSLATORS: $(XGETTEXT_OPTIONS)  \
	      --files-from=$(srcdir)/POTFILES.in \
	      --copyright-holder='$(COPYRIGHT_HOLDER)' \
	      --package-name="$${package_gnu}network-manager-applet" \
	      --package-version='1.8.24' \
	      --msgid-bugs-address="$$msgid_bugs_address" \
	    ;; \
	esac
	test ! -f $(DOMAIN).po || { \
	  if test -f $(srcdir)/$(DOMAIN).pot; then \
	    sed -f remove-potcdate.sed < $(srcdir)/$(DOMAIN).pot > $(DOMAIN).1po && \
	    sed -f remove-potcdate.sed < $(DOMAIN).po > $(DOMAIN).2po && \
	    if cmp $(DOMAIN).1po $(DOMAIN).2po >/dev/null 2>&1; then \
	      rm -f $(DOMAIN).1po $(DOMAIN).2po $(DOMAIN).po; \
	    else \
	      rm -f $(DOMAIN).1po $(DOMAIN).2po $(srcdir)/$(DOMAIN).pot && \
	      mv $(DOMAIN).po $(srcdir)/$(DOMAIN).pot; \
	    fi; \
	  else \
	    mv $(DOMAIN).po $(srcdir)/$(DOMAIN).pot; \
	  fi; \
	}

# This rule has no dependencies: we don't need to update $(DOMAIN).pot at
# every "make" invocation, only create it when it is missing.
# Only "make $(DOMAIN).pot-update" or "make dist" will force an update.
$(srcdir)/$(DOMAIN).pot:
	$(MAKE) $(DOMAIN).pot-update

# This target rebuilds a PO file if $(DOMAIN).pot has changed.
# Note that a PO file is not touched if it doesn't need to be changed.
$(POFILES): $(srcdir)/$(DOMAIN).pot
	@lang=`echo $@ | sed -e 's,.*/,,' -e 's/\.po$$//'`; \
	if test -f "$(srcdir)/$${lang}.po"; then \
	  test "$(srcdir)" = . && cdcmd="" || cdcmd="cd $(srcdir) && "; \
	  echo "$${cdcmd}$(MSGMERGE_UPDATE) $(MSGMERGE_OPTIONS) --lang=$${lang} $${lang}.po $(DOMAIN).pot"; \
	  cd $(srcdir) \
	    && { case `$(MSGMERGE_UPDATE) --version | sed 1q | sed -e 's,^[^0-9]*,,'` in \
	           '' | 0.[0-9] | 0.[0-9].* | 0.1[0-7] | 0.1[0-7].*) \
	             $(MSGMERGE_UPDATE) $(MSGMERGE_OPTIONS) $${lang}.po $(DOMAIN).pot;; \
	           *) \
	             $(MSGMERGE_UPDATE) $(MSGMERGE_OPTIONS) --lang=$${lang} $${lang}.po $(DOMAIN).pot;; \
	         esac; \
	       }; \
	else \
	  $(MAKE) $${lang}.po-create; \
	fi


install: install-exec install-data
install-exec:
install-data: install-data-yes
	if test "$(PACKAGE)" = "gettext-tools"; then \
	  $(mkdir_p) $(DESTDIR)$(gettextsrcdir); \
	  for file in $(DISTFILES.common) Makevars.template; do \
	    $(INSTALL_DATA) $(srcdir)/$$file \
			    $(DESTDIR)$(gettextsrcdir)/$$file; \
	  done; \
	  for file in Makevars; do \
	    rm -f $(DESTDIR)$(gettextsrcdir)/$$file; \
	  done; \
	else \
	  : ; \
	fi
install-data-no: all
install-data-yes: all
	@catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed -e 's/\.gmo$$//'`; \
	  dir=$(localedir)/$$lang/LC_MESSAGES; \
	  $(mkdir_p) $(DESTDIR)$$dir; \
	  if test -r $$cat; then realcat=$$cat; else realcat=$(srcdir)/$$cat; fi; \
	  $(INSTALL_DATA) $$realcat $(DESTDIR)$$dir/$(DOMAIN).mo; \
	  echo "installing $$realcat as $(DESTDIR)$$dir/$(DOMAIN).mo"; \
	  for lc in '' $(EXTRA_LOCALE_CATEGORIES); do \
	    if test -n "$$lc"; then \
	      if (cd $(DESTDIR)$(localedir)/$$lang && LC_ALL=C ls -l -d $$lc 2>/dev/null) | grep ' -> ' >/dev/null; then \
	        link=`cd $(DESTDIR)$(localedir)/$$lang && LC_ALL=C ls -l -d $$lc | sed -e 's/^.* -> //'`; \
	        mv $(DESTDIR)$(localedir)/$$lang/$$lc $(DESTDIR)$(localedir)/$$lang/$$lc.old; \
	        mkdir $(DESTDIR)$(localedir)/$$lang/$$lc; \
	        (cd $(DESTDIR)$(localedir)/$$lang/$$lc.old && \
	         for file in *; do \
	           if test -f $$file; then \
	             ln -s ../$$link/$$file $(DESTDIR)$(localedir)/$$lang/$$lc/$$file; \
	           fi; \
	         done); \
	        rm -f $(DESTDIR)$(localedir)/$$lang/$$lc.old; \
	      else \
	        if test -d $(DESTDIR)$(localedir)/$$lang/$$lc; then \
	          :; \
	        else \
	          rm -f $(DESTDIR)$(localedir)/$$lang/$$lc; \
	          mkdir $(DESTDIR)$(localedir)/$$lang/$$lc; \
	        fi; \
	      fi; \
	      rm -f $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo; \
	      ln -s ../LC_MESSAGES/$(DOMAIN).mo $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo 2>/dev/null || \
	      ln $(DESTDIR)$(localedir)/$$lang/LC_MESSAGES/$(DOMAIN).mo $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo 2>/dev/null || \
	      cp -p $(DESTDIR)$(localedir)/$$lang/LC_MESSAGES/$(DOMAIN).mo $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo; \
	      echo "installing $$realcat link as $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo"; \
	    fi; \
	  done; \
	done

install-strip: install

installdirs: installdirs-exec installdirs-data
installdirs-exec:
installdirs-data: installdirs-data-yes
	if test "$(PACKAGE)" = "gettext-tools"; then \
	  $(mkdir_p) $(DESTDIR)$(gettextsrcdir); \
	else \
	  : ; \
	fi
installdirs-data-no:
installdirs-data-yes:
	@catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed -e 's/\.gmo$$//'`; \
	  dir=$(localedir)/$$lang/LC_MESSAGES; \
	  $(mkdir_p) $(DESTDIR)$$dir; \
	  for lc in '' $(EXTRA_LOCALE_CATEGORIES); do \
	    if test -n "$$lc"; then \
	      if (cd $(DESTDIR)$(localedir)/$$lang && LC_ALL=C ls -l -d $$lc 2>/dev/null) | grep ' -> ' >/dev/null; then \
	        link=`cd $(DESTDIR)$(localedir)/$$lang && LC_ALL=C ls -l -d $$lc | sed -e 's/^.* -> //'`; \
	        mv $(DESTDIR)$(localedir)/$$lang/$$lc $(DESTDIR)$(localedir)/$$lang/$$lc.old; \
	        mkdir $(DESTDIR)$(localedir)/$$lang/$$lc; \
	        (cd $(DESTDIR)$(localedir)/$$lang/$$lc.old && \
	         for file in *; do \
	           if test -f $$file; then \
	             ln -s ../$$link/$$file $(DESTDIR)$(localedir)/$$lang/$$lc/$$file; \
	           fi; \
	         done); \
	        rm -f $(DESTDIR)$(localedir)/$$lang/$$lc.old; \
	      else \
	        if test -d $(DESTDIR)$(localedir)/$$lang/$$lc; then \
	          :; \
	        else \
	          rm -f $(DESTDIR)$(localedir)/$$lang/$$lc; \
	          mkdir $(DESTDIR)$(localedir)/$$lang/$$lc; \
	        fi; \
	      fi; \
	    fi; \
	  done; \
	done

# Define this as empty until I found a useful application.
installcheck:

uninstall: uninstall-exec uninstall-data
uninstall-exec:
uninstall-data: uninstall-data-yes
	if test "$(PACKAGE)" = "gettext-tools"; then \
	  for file in $(DISTFILES.common) Makevars.template; do \
	    rm -f $(DESTDIR)$(gettextsrcdir)/$$file; \
	  done; \
	else \
	  : ; \
	fi
uninstall-data-no:
uninstall-data-yes:
	catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed -e 's/\.gmo$$//'`; \
	  for lc in LC_MESSAGES $(EXTRA_LOCALE_CATEGORIES); do \
	    rm -f $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo; \
	  done; \
	done

check: all

info dvi ps pdf html tags TAGS ctags CTAGS ID:

mostlyclean:
	rm -f remove-potcdate.sed
	rm -f stamp-poT
	rm -f core core.* $(DOMAIN).po $(DOMAIN).1po $(DOMAIN).2po *.new.po
	rm -fr *.o

clean: mostlyclean

distclean: clean
	rm -f Makefile Makefile.in POTFILES *.mo

maintainer-clean: distclean
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."
	rm -f stamp-po $(GMOFILES)

distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)
dist distdir:
	$(MAKE) update-po
	@$(MAKE) dist2
# This is a separate target because 'update-po' must be executed before.
dist2: stamp-po $(DISTFILES)
	dists="$(DISTFILES)"; \
	if test "$(PACKAGE)" = "gettext-tools"; then \
	  dists="$$dists Makevars.template"; \
	fi; \
	if test -f $(srcdir)/$(DOMAIN).pot; then \
	  dists="$$dists $(DOMAIN).pot stamp-po"; \
	fi; \
	if test -f $(srcdir)/ChangeLog; then \
	  dists="$$dists ChangeLog"; \
	fi; \
	for i in 0 1 2 3 4 5 6 7 8 9; do \
	  if test -f $(srcdir)/ChangeLog.$$i; then \
	    dists="$$dists ChangeLog.$$i"; \
	  fi; \
	done; \
	if test -f $(srcdir)/LINGUAS; then dists="$$dists LINGUAS"; fi; \
	for file in $$dists; do \
	  if test -f $$file; then \
	    cp -p $$file $(distdir) || exit 1; \
	  else \
	    cp -p $(srcdir)/$$file $(distdir) || exit 1; \
	  fi; \
	done

update-po: Makefile
	$(MAKE) $(DOMAIN).pot-update
	test -z "$(UPDATEPOFILES)" || $(MAKE) $(UPDATEPOFILES)
	$(MAKE) update-gmo

# General rule for creating PO files.

.nop.po-create:
	@lang=`echo $@ | sed -e 's/\.po-create$$//'`; \
	echo "File $$lang.po does not exist. If you are a translator, you can create it through 'msginit'." 1>&2; \
	exit 1

# General rule for updating PO files.

.nop.po-update:
	@lang=`echo $@ | sed -e 's/\.po-update$$//'`; \
	if test "$(PACKAGE)" = "gettext-tools"; then PATH=`pwd`/../src:$$PATH; fi; \
	tmpdir=`pwd`; \
	echo "$$lang:"; \
	test "$(srcdir)" = . && cdcmd="" || cdcmd="cd $(srcdir) && "; \
	echo "$${cdcmd}$(MSGMERGE) $(MSGMERGE_OPTIONS) --lang=$$lang $$lang.po $(DOMAIN).pot -o $$lang.new.po"; \
	cd $(srcdir); \
	if { case `$(MSGMERGE) --version | sed 1q | sed -e 's,^[^0-9]*,,'` in \
	       '' | 0.[0-9] | 0.[0-9].* | 0.1[0-7] | 0.1[0-7].*) \
	         $(MSGMERGE) $(MSGMERGE_OPTIONS) -o $$tmpdir/$$lang.new.po $$lang.po $(DOMAIN).pot;; \
	       *) \
	         $(MSGMERGE) $(MSGMERGE_OPTIONS) --lang=$$lang -o $$tmpdir/$$lang.new.po $$lang.po $(DOMAIN).pot;; \
	     esac; \
	   }; then \
	  if cmp $$lang.po $$tmpdir/$$lang.new.po >/dev/null 2>&1; then \
	    rm -f $$tmpdir/$$lang.new.po; \
	  else \
	    if mv -f $$tmpdir/$$lang.new.po $$lang.po; then \
	      :; \
	    else \
	      echo "msgmerge for $$lang.po failed: cannot move $$tmpdir/$$lang.new.po to $$lang.po" 1>&2; \
	      exit 1; \
	    fi; \
	  fi; \
	else \
	  echo "msgmerge for $$lang.po failed!" 1>&2; \
	  rm -f $$tmpdir/$$lang.new.po; \
	fi

$(DUMMYPOFILES):

update-gmo: Makefile $(GMOFILES)
	@:

# Recreate Makefile by invoking config.status. Explicitly invoke the shell,
# because execution permission bits may not work on the current file system.
# Use /bin/bash, which is the shell determined by autoconf for the use by its
# scripts, not $(SHELL) which is hardwired to /bin/sh and may be deficient.
Makefile: Makefile.in.in Makevars $(top_builddir)/config.status POTFILES.in LINGUAS
	cd $(top_builddir) \
	  && /bin/bash ./config.status $(subdir)/$@.in po-directories

force:

# Tell versions [3.59,3.63) of GNU make not to export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
# Special Makefile rules for English message catalogs with quotation marks.

DISTFILES.common.extra1 = quot.sed boldquot.sed en@quot.header en@boldquot.header insert-header.sin Rules-quot

.SUFFIXES: .insert-header .po-update-en

en@quot.po-create:
	$(MAKE) en@quot.po-update
en@boldquot.po-create:
	$(MAKE) en@boldquot.po-update

en@quot.po-update: en@quot.po-update-en
en@boldquot.po-update: en@boldquot.po-update-en

.insert-header.po-update-en:
	@lang=`echo $@ | sed -e 's/\.po-update-en$$//'`; \
	if test "$(PACKAGE)" = "gettext"; then PATH=`pwd`/../src:$$PATH; GETTEXTLIBDIR=`cd $(top_srcdir)/src && pwd`; export GETTEXTLIBDIR; fi; \
	tmpdir=`pwd`; \
	echo "$$lang:"; \
	ll=`echo $$lang | sed -e 's/@.*//'`; \
	LC_ALL=C; export LC_ALL; \
	cd $(srcdir); \
	if $(MSGINIT) -i $(DOMAIN).pot --no-translator -l $$lang -o - 2>/dev/null | sed -f $$tmpdir/$$lang.insert-header | $(MSGCONV) -t UTF-8 | $(MSGFILTER) sed -f `echo $$lang | sed -e 's/.*@//'`.sed 2>/dev/null > $$tmpdir/$$lang.new.po; then \
	  if cmp $$lang.po $$tmpdir/$$lang.new.po >/dev/null 2>&1; then \
	    rm -f $$tmpdir/$$lang.new.po; \
	  else \
	    if mv -f $$tmpdir/$$lang.new.po $$lang.po; then \
	      :; \
	    else \
	      echo "creation of $$lang.po failed: cannot move $$tmpdir/$$lang.new.po to $$lang.po" 1>&2; \
	      exit 1; \
	    fi; \
	  fi; \
	else \
	  echo "creation of $$lang.po failed!" 1>&2; \
	  rm -f $$tmpdir/$$lang.new.po; \
	fi

en@quot.insert-header: insert-header.sin
	sed -e '/^#/d' -e 's/HEADER/en@quot.header/g' $(srcdir)/insert-header.sin > en@quot.insert-header

en@boldquot.insert-header: insert-header.sin
	sed -e '/^#/d' -e 's/HEADER/en@boldquot.header/g' $(srcdir)/insert-header.sin > en@boldquot.insert-header

mostlyclean: mostlyclean-quot
mostlyclean-quot:
	rm -f *.insert-header
