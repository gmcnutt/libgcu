# cutils
Common re-usable C utility functions.

# installing
This will install libcu.so in ~/lib and the .h files in ~/include:

```make install```

# using
To compile app.c against this lib:

```gcc -I ~/include -L ~/lib -o app app.c -lcu```

To run:

```
export LD_LIBRARY_PATH=~/lib:$LD_LIBRARY_PATH
./app
```
