#some variable for data directory defined here "These Value Can use in source file"
INCLUDES =	-DGBEE_RESOURCES=\"$(datadir)/gbee/Resources\" 
#            -DIJADI_UI=\"$(datadir)/ijadi/UI\" \
#            -DIJADI_SCRIPT=\"$(datadir)/ijadi/Script\"

bin_PROGRAMS = Gbee

Gbee_SOURCES = main.c \
	gbee-intercept.h \
	gbee-intercept.c \
	gbee-define.h \
	gbee-parser.c \
	gbee-parser.h \
	gbee-string.c \
	gbee-string.h \
	gbee-iparser.c \
	gbee-iparser.h 

Gbee_CFLAGS = $(GTK_CFLAGS) -g -O0

Gbee_LDFLAGS = $(GTK_LIBS) $(SQLITE3_LIBS)
