
#Ensure that lates version of autoconf avalible
AC_PREREQ([2.63])

#create info about project
AC_INIT([Ijadi],[0.1], , Ijadi)

#foreign use to break the gnu strict
AM_INIT_AUTOMAKE([foreign dist-bzip2])

#create information for package
AC_CONFIG_HEADERS([config.h])

# Use it to link library
AC_PROG_LIBTOOL


# Checks for programs.
AC_PROG_CC
AC_PROG_CXX

PKG_CHECK_MODULES([GTK], [gtk+-3.0  >= 3.2.0])
PKG_CHECK_MODULES([CAIRO], [cairo >= 1.0.0])
PKG_CHECK_MODULES([GDK], [gdk-3.0 >= 2.91.7])
PKG_CHECK_MODULES([LIBANJUTA],[libanjuta-3.0])
#force to less verbose build output
AM_SILENT_RULES([yes])

AC_CONFIG_FILES([
	Makefile
	Source/Makefile
  Resources/Makefile
  Resources/UI/Makefile
  Script/Makefile
])

AC_OUTPUT

