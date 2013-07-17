#some variable for data directory defined here "These Value Can use in source file"
INCLUDES =	-DIJADI_RESOURCES=\"$(datadir)/ijadi/Resources\" \
            -DIJADI_UI=\"$(datadir)/ijadi/UI\" \
            -DIJADI_SCRIPT=\"$(datadir)/ijadi/Script\"

bin_PROGRAMS = ijadi

ijadi_SOURCES = main.c ijadi-gui.h ijadi-gui.c ijadi-application.h ijadi-application.c ijadi-wizard.h ijadi-wizard.c ijadi-define.h

ijadi_CFLAGS = $(GTK_CFLAGS) $(LIBANJUTA_CFLAGS)

ijadi_LDFLAGS = $(GTK_LIBS) $(LIBANJUTA_LIBS)
