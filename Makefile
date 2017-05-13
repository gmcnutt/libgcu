lib := libcu.so
installdir := ~
libdir := $(installdir)/lib
incdir := $(installdir)/include
sources := $(wildcard *.c)
hdrs := $(wildcard *.h)
objects = $(sources:.c=.o)
CFLAGS += -Werror -Wfatal-errors
CFLAGS += -std=c99
CFLAGS += -shared -fPIC

ifeq ($(OPTIMIZE), true)
	CFLAGS += -O2
else
	CFLAGS += -Wall -g
endif

all: $(lib)

$(libdir) $(incdir):
	mkdir -p $@

install: $(lib) $(libdir) $(incdir)
	cp $(lib) $(libdir)
	cp $(hdrs) $(incdir)

$(lib): $(objects) Makefile
	$(CC) $(CFLAGS) -o $@ $(objects) -Wl,-rpath=/usr/local/lib

clean:
	rm -f $(lib) $(objects)
