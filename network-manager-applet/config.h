/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define to 1 if translation of program messages to the user's native
   language is requested. */
#define ENABLE_NLS 1

/* Gettext package */
#define GETTEXT_PACKAGE "nm-applet"

/* Define to 1 if you have the MacOS X function CFLocaleCopyCurrent in the
   CoreFoundation framework. */
/* #undef HAVE_CFLOCALECOPYCURRENT */

/* Define to 1 if you have the MacOS X function CFPreferencesCopyAppValue in
   the CoreFoundation framework. */
/* #undef HAVE_CFPREFERENCESCOPYAPPVALUE */

/* Define if the GNU dcgettext() function is already present or preinstalled.
   */
#define HAVE_DCGETTEXT 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define if the GNU gettext() function is already present or preinstalled. */
#define HAVE_GETTEXT 1

/* Define if you have the iconv() function and it works. */
/* #undef HAVE_ICONV */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define if you have libnotify 0.7 or later */
#define HAVE_LIBNOTIFY_07 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* ISO codes prefix */
#define ISO_CODES_PREFIX "/usr"

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* Mobile Broadband Service Provider Information Database location */
#define MOBILE_BROADBAND_PROVIDER_INFO_DATABASE "/usr/share/mobile-broadband-provider-info/serviceproviders.xml"

/* git commit id of the original source code version */
#define NMA_GIT_SHA ""

/* Define if more asserts are enabled */
#define NM_MORE_ASSERTS 0

/* Name of package */
#define PACKAGE "network-manager-applet"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "https://gitlab.gnome.org/GNOME/network-manager-applet/issues"

/* Define to the full name of this package. */
#define PACKAGE_NAME "nm-applet"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "nm-applet 1.8.24"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "network-manager-applet"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.8.24"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Explicitly enforce Ayatana AppIndicator */
#define USE_AYATANA_INDICATORS 0

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Version number of package */
#define VERSION "1.8.24"

/* Enable AppIndicator support and use Ubuntu AppIndicator */
#define WITH_APPINDICATOR 1

/* Define if Gcr is available */
#define WITH_GCR 1

/* Define if GTK4 Gcr is available */
#define WITH_GCR_GTK4 0

/* Define if Jansson is available */
#define WITH_JANSSON 1

/* Define if libselinux is available */
#define WITH_SELINUX 1

/* Define if you have ModemManager/WWAN support */
#define WITH_WWAN 1

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */
