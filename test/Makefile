program = test
sources := $(wildcard *.c) $(wildcard ../*.c)
hdrs := $(wildcard *.h) $(wildcard ../*.h)
objects = $(sources:.c=.o)
CFLAGS = -Wall -g -std=c99
CFLAGS += -I ../
CFLAGS += -Werror -Wfatal-errors
CFLAGS += -fprofile-arcs -ftest-coverage
LDLIBS += -lm

all: $(program)

$(program): $(objects)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -f $(program) $(objects) *.gcov *.gcda *.gcno *.d
