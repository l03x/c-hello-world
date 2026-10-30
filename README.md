# c-hello-world

A small C program that prints "Hello world" without a single `#include`. Since there are no headers, it can't use `printf` or any other output function from the C standard library. Instead, `print` in `main.c` counts the length of the string itself and calls the Linux `write` system call directly with inline assembly.

Each supported architecture has its own `print`, and the preprocessor picks the right one at compile time. All of them are Linux only. Building for any other architecture stops with an "unsupported architecture" error.

## Build and run

You need `gcc` and `make`.

```bash
make
./main
```

To build for another architecture, pass a cross compiler, for example:

```bash
make CC=aarch64-linux-gnu-gcc
```

To remove the compiled binary:

```bash
make clean
```
