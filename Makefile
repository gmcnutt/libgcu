lib := libgcu.so
installdir := ~
libdir := $(installdir)/lib
incdir := $(installdir)/include
sources := $(wildcard *.c)
hdrs := $(wildcard *.h)
objects = $(sources:.c=.o)
testsrc := test/test.c
CFLAGS := -Werror -Wfatal-errors -std=c99
LDFLAGS += -lm

# Auto-generate .h dependency rules
CFLAGS += -MD -MP

# Turn the result into a linkable library
CFLAGS += -shared -fPIC

ifeq ($(OPTIMIZE), true)
	CFLAGS += -O2
else
	CFLAGS += -Wall -g -O0 -fprofile-arcs -ftest-coverage
endif

.PHONY: clean indent all runtest

all: $(lib)

$(libdir) $(incdir):
	mkdir -p $@

install: $(lib) $(libdir) $(incdir)
	cp $(lib) $(libdir)
	cp $(hdrs) $(incdir)

$(lib): $(objects) Makefile
	$(CC) $(CFLAGS) $(LIBCFLAGS) -o $@ $(objects) $(LDFLAGS) -Wl,-rpath=/usr/local/lib

clean:
	rm -f $(lib) $(objects) *.gcov *.gcda *.gcno *.d
	$(MAKE) -C test clean

indent: $(sources) $(hdrs) $(testsrc)
	indent -linux $^
	sed -i 's/[ \t]*$$//' $^


runtest: $(objects) $(testsrc)
	$(MAKE) -C test
	valgrind ./test/test

# Include the dependency rules generated by -MD -MP
-include $(sources:%.c=%.d)
