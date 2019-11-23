# Gmcnutt's C Utilities (libgcu)

Common re-usable C utility functions that I like to use in my C projects.

# Dependencies

Just a standard C development environment.

# installing

I like to install in my home directory. This will install libcu.so in
~/lib and the .h files in ~/include:

```make install```

# using

Put the header in your hypothetical `app.c`:

`#include <gcu.h>`

To compile and link `app.c` against this lib:

```gcc -I ~/include -L ~/lib  -Wl,-rpath=$HOME/lib -o app yapp.c -lgcu```
