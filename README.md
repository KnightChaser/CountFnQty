# CountFnQty

Using LLVM, it counts the number of functions (function definitions) and function calls in C/C++ source files.
I just wanted to learn how to use LLVM for source code analysis. Nothing special. >v<

## Build

```sh
meson setup builddir --native-file clang.ini
meson compile -C builddir
```

## Run

(Note: Adjust the include path and language standard according to your environment.)

```sh
cd builddir
./src/CountFnQty ../test/is_prime.cpp -- -I/usr/lib/clang/21/include -std=c++17
./src/CountFnQty ../test/is_prime.c -- -I/usr/lib/clang/21/include
```

## Example Output

```text
$ ./src/CountFnQty ../test/is_prime.c -- -I/usr/lib/clang/21/include

Number of function declarations: 2
Number of function calls: 6
```
