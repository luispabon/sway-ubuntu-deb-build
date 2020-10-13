AC_PREREQ([2.63])

m4_define([nm_applet_major_version], [1])
m4_define([nm_applet_minor_version], [18])
m4_define([nm_applet_micro_version], [0])
m4_define([nm_applet_version],
          [nm_applet_major_version.nm_applet_minor_version.nm_applet_micro_version])

AC_INIT([nm-applet],
        [nm_applet_version],
        [https://gitlab.gnome.org/GNOME/network-manager-applet/issues],
        [network-manager-applet])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.11 no-dist-gzip dist-xz -Wno-portability])
AM_MAINTAINER_MODE([enable])
AM_SILENT_RULES([yes])

dnl
dnl Require programs
dnl
AC_PROG_CC
AM_PROG_CC_C_O
PKG_PROG_PKG_CONFIG

AC_CHECK_PROG([has_file], file, yes, no)
if test x$has_file = xno ; then
    AC_MSG_ERROR(["file" utility not found.])
fi

AC_CHECK_PROG([has_find], find, yes, no)
if test x$has_find = xno ; then
    AC_MSG_ERROR(["find" utility not found.])
fi

dnl Define _GNU_SOURCE for various things like strcasestr()
AC_USE_SYSTEM_EXTENSIONS

dnl Initialize libtool
LT_PREREQ([2.2.6])
LT_INIT

GIT_SHA_RECORD(NMA_GIT_SHA)

dnl
dnl Checks for typedefs, structures, and compiler characteristics.
dnl
AC_TYPE_PID_T

dnl
dnl translation support
dnl
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.18])

GETTEXT_PACKAGE=nm-applet
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [Gettext package])

PKG_CHECK_MODULES(LIBNM, [libnm >= 1.15 gio-2.0 >= 2.38 gmodule-export-2.0])
LIBNM_CFLAGS="$LIBNM_CFLAGS -DGLIB_VERSION_MIN_REQUIRED=GLIB_VERSION_2_38"
LIBNM_CFLAGS="$LIBNM_CFLAGS -DGLIB_VERSION_MAX_ALLOWED=GLIB_VERSION_2_38"
LIBNM_CFLAGS="$LIBNM_CFLAGS -DNM_VERSION_MIN_REQUIRED=NM_VERSION_1_16"
LIBNM_CFLAGS="$LIBNM_CFLAGS -DNM_VERSION_MAX_ALLOWED=NM_VERSION_1_16"

PKG_CHECK_MODULES(LIBNMA, libnma >= 1.8.27)
LIBNMA_CFLAGS="$LIBNMA_CFLAGS -DNMA_VERSION_MIN_REQUIRED=NMA_VERSION_1_8_28"
LIBNMA_CFLAGS="$LIBNMA_CFLAGS -DNMA_VERSION_MAX_ALLOWED=NMA_VERSION_1_8_28"

PKG_CHECK_MODULES(LIBSECRET, [libsecret-1 >= 0.18])

# Check for libnotify >= 0.7
PKG_CHECK_MODULES(LIBNOTIFY_07, [libnotify >= 0.7], [have_libnotify_07=yes],[have_libnotify_07=no])
if test x"$have_libnotify_07" = "xyes"; then
	AC_DEFINE(HAVE_LIBNOTIFY_07, 1, [Define if you have libnotify 0.7 or later])
fi
PKG_CHECK_MODULES(NOTIFY, [libnotify >= 0.4.3])

PKG_CHECK_MODULES(GTK3, gtk+-3.0 >= 3.10)
GTK3_CFLAGS="$GTK3_CFLAGS -DGDK_VERSION_MIN_REQUIRED=GDK_VERSION_3_10 -DGDK_VERSION_MAX_ALLOWED=GDK_VERSION_3_10"

AC_ARG_WITH([appindicator],
            AS_HELP_STRING([--with-appindicator=no|yes|auto|ayatana|ubuntu], [Build with lib(ayatana-)appindicator support in addition to xembed systray support.]),
            [], [with_appindicator=auto])
if test "$with_appindicator" != "no"; then
	if test "$with_appindicator" = "yes" -o "$with_appindicator" = "auto"; then
		PKG_CHECK_MODULES(APPINDICATOR, ayatana-appindicator3-0.1, [with_appindicator=ayatana], [with_appindicator=no])
		if test "$with_appindicator" = "no"; then
			PKG_CHECK_MODULES(APPINDICATOR, appindicator3-0.1, [with_appindicator=ubuntu], [with_appindicator=no])
			if test "$with_appindicator" = "no"; then
				AC_MSG_ERROR([Neither Ubuntu's AppIndicator nor Ayatana AppIndicator found. Better --without-appindicator?])
			fi
		fi
	elif test "$with_appindicator" = "ayatana"; then
		PKG_CHECK_MODULES(APPINDICATOR, ayatana-appindicator3-0.1)
	elif test "$with_appindicator" = "ubuntu"; then
		PKG_CHECK_MODULES(APPINDICATOR, appindicator3-0.1)
	else
		AC_MSG_ERROR([Invalid --with-appindicator option. Must be one of no|yes|auto|ayatana|ubuntu])
	fi

	if test "$with_appindicator" = "ayatana"; then
		PKG_CHECK_MODULES(DBUSMENU, dbusmenu-gtk3-0.4 >= 16.04.0)
		AC_DEFINE([WITH_APPINDICATOR], 1, [Enable AppIndicator support and use Ayatana AppIndicator])
		AC_DEFINE([USE_AYATANA_INDICATORS], 1, [Explicitly enforce Ayatana AppIndicator])
	else
		PKG_CHECK_MODULES(DBUSMENU, dbusmenu-gtk3-0.4 >= 16.04.0)
		AC_DEFINE([WITH_APPINDICATOR], 1, [Enable AppIndicator support and use Ubuntu AppIndicator])
		AC_DEFINE([USE_AYATANA_INDICATORS], 0, [Explicitly enforce Ayatana AppIndicator])
	fi
fi

dnl ModemManager1 with libmm-glib for WWAN support
AC_ARG_WITH(wwan, AS_HELP_STRING([--with-wwan], [Enable WWAN support (default: yes)]))
if (test "${with_wwan}" == "no"); then
    AC_DEFINE(WITH_WWAN, 0, [Define if you have ModemManager/WWAN support])
else
    PKG_CHECK_MODULES(MM_GLIB,
                      [mm-glib],,
                      AC_MSG_ERROR([libmm-glib is needed for WWAN support. Use --without-wwan to build without it.]))
    AC_DEFINE(WITH_WWAN, 1, [Define if you have ModemManager/WWAN support])
fi
AM_CONDITIONAL(WITH_WWAN, test "${with_wwan}" != "no")

dnl Check for gudev
PKG_CHECK_MODULES(GUDEV, gudev-1.0 >= 147)

dnl SELinux
AC_ARG_WITH(selinux, AS_HELP_STRING([--with-selinux], [Enable support for adjusting SELinux labels in configuration editor (default: yes)]))
if (test "${with_selinux}" == "no"); then
    AC_DEFINE(WITH_SELINUX, 0, [Define if libselinux is available])
else
    PKG_CHECK_MODULES(SELINUX,
                      [libselinux],,
                      AC_MSG_ERROR([libselinux is needed for SELinux label support in configuration editor. Use --without-selinux to build without it.]))
    AC_DEFINE(WITH_SELINUX, 1, [Define if libselinux is available])
fi
AM_CONDITIONAL(WITH_SELINUX, test "${with_selinux}" != "no")

dnl Jansson for team configuration editing
AC_ARG_WITH(team, AS_HELP_STRING([--with-team], [Enable team configuration editor (default: yes)]))
if (test "${with_team}" == "no"); then
    AC_DEFINE(WITH_JANSSON, 0, [Define if Jansson is available])
else
    PKG_CHECK_MODULES(JANSSON,
                      [jansson >= 2.7],,
                      AC_MSG_ERROR([jansson is needed for team configuration editor. Use --without-team to build without it.]))
    AC_DEFINE(WITH_JANSSON, 1, [Define if Jansson is available])
fi
AM_CONDITIONAL(WITH_JANSSON, test "${with_team}" != "no")

GLIB_CONFIG_NMA
GLIB_GSETTINGS
AC_PATH_PROG(GLIB_COMPILE_RESOURCES, glib-compile-resources)

NM_COMPILER_WARNINGS(CFLAGS, [yes])
NM_LTO
NM_LD_GC

AC_ARG_WITH(more-asserts,
            AS_HELP_STRING([--with-more-asserts=level], [Enable more assertions for debugging (default: 0)]),
            [more_asserts=${with_more_asserts}],
            [more_asserts=no])
if test "${more_asserts}" = "no"; then
    more_asserts=0
else
    if test "${more_asserts}" = "yes"; then
        more_asserts=100
    fi
fi
AC_DEFINE_UNQUOTED(NM_MORE_ASSERTS, $more_asserts, [Define if more asserts are enabled])


AC_CONFIG_FILES([
Makefile
man/nm-applet.1
man/nm-connection-editor.1
po/Makefile.in
])
AC_OUTPUT

echo ""
echo "  LTO: --enable-lto=$enable_lto"
echo "  Linker garbage collection: --enable-ld-gc=$enable_ld_gc"
echo "  appindicator: $with_appindicator"
echo ""
