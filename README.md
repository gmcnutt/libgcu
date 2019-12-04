# Gmcnutt's C Utilities (libgcu)

Common re-usable C utility functions that I like to use in my C projects.

# Dependencies

Just a standard C development environment.

# Installing

I like to install in my home directory. This will install libcu.so in
~/lib and the .h files in ~/include:

```make install```

# Using

Put the header in your hypothetical `app.c`:

`#include <gcu.h>`

To compile and link `app.c` against this lib:

```gcc -I ~/include -L ~/lib  -Wl,-rpath=$HOME/lib -o app yapp.c -lgcu```

# Conventions

* All of the `_alloc()` function return a newly allocated object that has a
single refcount on it. All of these objects support `mem_ref()` and
`mem_deref()`.

* All of the `_deref()` functions are just aliases for `mem_deref()`.

* All of the container objects, like `hash` and `grid`, call `mem_ref()` and
`mem_deref()` on their `userdata` args. That means `userdata` should be a
result of one of the `_alloc()` calls.

