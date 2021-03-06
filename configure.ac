dnl Process this file with autoconf to produce a configure script.

AC_INIT([FoxtrotGPS], [1.2.0+], [foss-gps@lists.osgeo.org])
AM_INIT_AUTOMAKE([-Wall -Werror -Wno-portability])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE([enable])

AC_PROG_CC_C99
AC_HEADER_STDC
AM_SILENT_RULES([yes])

GETTEXT_PACKAGE=foxtrotgps
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [Package name for gettext])
IT_PROG_INTLTOOL([0.23])

dnl Languages which your application supports
ALL_LINGUAS="bg cs de es fi fr hu ru sk nl ja sr pt_BR pl it"
AM_GLIB_GNU_GETTEXT

AC_PROG_LN_S
LT_INIT

PKG_CHECK_MODULES(GTK, [gtk+-2.0 gdk-2.0 gthread-2.0])
PKG_CHECK_MODULES(GLADE, [libglade-2.0])
PKG_CHECK_MODULES(GCONF, [gconf-2.0])
PKG_CHECK_MODULES(LIBCURL, [libcurl])
PKG_CHECK_MODULES(SQLITE, [sqlite3])
PKG_CHECK_MODULES(LIBEXIF, [libexif])
PKG_CHECK_MODULES(LIBXML, [libxml-2.0])
PKG_CHECK_MODULES(LIBGPS, [libgps >= 2.90])
PKG_CHECK_MODULES(BLUETOOTH, [bluez],
                  [AC_DEFINE(HAVE_BLUEZ, [],
                             [We have the BlueZ bluetooth library])
                   AC_DEFINE(ENABLE_HRM, [],
                             [Heartrate-monitor support is enabled])],
                  [AC_MSG_WARN([Building without heartrate-monitor support])])

AC_PATH_PROG(GCONFTOOL2, [gconftool-2])
if test -z "$GCONFTOOL2"
then
    AC_MSG_ERROR([gconftool-2 is required for installation.])
fi

AM_GCONF_SOURCE_2

AC_CONFIG_FILES([
Makefile
po/Makefile.in
src/Makefile
pixmaps/Makefile
data/Makefile
doc/Makefile
contrib/Makefile
])
AC_OUTPUT
