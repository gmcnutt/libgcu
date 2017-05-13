lib := libcu.so
sources := $(wildcard *.c)
objects = $(sources:.c=.o)
CFLAGS += -Werror -Wfatal-errors
CFLAGS += -std=c99
CFLAGS += -fPIC

ifeq ($(OPTIMIZE), true)
	CFLAGS += -O2
else
	CFLAGS += -Wall -g
endif

all: $(lib)

$(lib): $(objects) Makefile
	$(CC) -shared $(CFLAGS) -o $@ $(objects) -Wl,-rpath=/usr/local/lib

clean:
	rm -f $(lib) $(objects)
