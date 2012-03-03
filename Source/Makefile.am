#some variable for data directory defined here
INCLUDES =	-DIJADI_RESOURCES=\"$(datadir)/ijadi/Resources\"

bin_PROGRAMS = ijadi

ijadi_SOURCES = main.c ijadi-gui.h ijadi-gui.c ijadi-application.h ijadi-application.c ijadi-wizard.h ijadi-wizard.c ijadi-define.h

ijadi_CFLAGS = $(GTK_CFLAGS)

ijadi_LDFLAGS = $(GTK_LIBS)
