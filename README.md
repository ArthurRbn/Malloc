# Malloc

Reimplement memory allocation functions from C standard library.

Reimplemented functions :
- ``malloc()``
- ``calloc()``
- ``realloc()``
- ``reallocarray()``
- ``free()``

To test my implementation clone the repository, compile the shared lib using ``make`` and compile a test main or any program using malloc with the library ``libmy_malloc.so``. If you want to be sure to load my malloc version you can load the symbol using ``dlopen()``, ``dlsym()`` and ``dlclose()``.

Mark : 16/20
