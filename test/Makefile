program = test
sources := $(wildcard *.c)
hdrs := $(wildcard *.h)
objects = $(sources:.c=.o)
CFLAGS = -Wall -g -std=c99
CFLAGS += -I ~/include -L ~/lib -Wl,-rpath=$(HOME)/lib
CFLAGS += -Werror -Wfatal-errors
CFLAGS += -fPIC
LDLIBS = -lgcu

all: $(program)

$(program): $(objects)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -f $(program) $(objects)
