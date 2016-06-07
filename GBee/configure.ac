
#Ensure that lates version of autoconf avalible
AC_PREREQ([2.63])

#create info about project
AC_INIT([Gbee],[0.1], , Gbee)

#foreign use to break the gnu strict
AM_INIT_AUTOMAKE([foreign dist-bzip2])

#create information for package
AC_CONFIG_HEADERS([config.h])

# Use it to link library
AC_PROG_LIBTOOL

# check for gtk-doc
GTK_DOC_CHECK([1.14],[--flavour no-tmpl])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX

PKG_CHECK_MODULES([GTK], [gtk+-3.0  >= 3.2.0])
PKG_CHECK_MODULES([SQLITE3], [sqlite3  >= 3.7.9])
#force to less verbose build output
AM_SILENT_RULES([yes])

AC_CONFIG_FILES([
	Makefile
	Source/Makefile
  Resources/Makefile
])

AC_OUTPUT

