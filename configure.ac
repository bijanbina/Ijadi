
#Ensure that lates version of autoconf avalible
AC_PREREQ([2.63])
#create info about project
AC_INIT([Ijadi],[0.1], , Ijadi)

AM_INIT_AUTOMAKE([foreign dist-bzip2])

# Use it to link library
AC_PROG_LIBTOOL

# check for gtk-doc
GTK_DOC_CHECK([1.14],[--flavour no-tmpl])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX

PKG_CHECK_MODULES([CLUTTER], [clutter-1.0 >= 1.8.0])
PKG_CHECK_MODULES([GTK], [gtk+-3.0  >= 3.0.0])
PKG_CHECK_MODULES([CAIRO], [cairo >= 1.0.0])
PKG_CHECK_MODULES(GDK, [gdk-3.0 >= 2.91.7])
#force to less verbose build output
AM_SILENT_RULES([yes])

AC_CONFIG_FILES([
	Makefile
	Source/Makefile
])

AC_OUTPUT

