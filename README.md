# Python.Cpp
A cpp library that provides useful utilities to use pythonic features in C++. Still under development

All you need to do is include the header file by using `#include "Python.h"`.
You can then access all utilities from the `py` namespace (e.g: `py::print("Hello world!)`)
Some examples can be found in the `Python.cpp` file.

## Supported utilities
### Pythonic functions
 - `py::print()` can print one or more items of the same type. Like python supports `sep`, `end` and `flush` parameters except for `file` (coming soon).
 - `py::assert()` stops the program execution if the provided condition is false. Assertion Behavior can be changed by changing `py::DefaultAssertionFunctionPtr` reference.
 - `py::len()` and ` lenght()` works with every object which has either `lenght()` or `__len__()` methods. `len()` returns an integer while `lenght()` returns size_t.

## Coming soon
 - Pytonic file system
 - other useful pythonic functions
 - Pythonic data structures (like str, list, tuple, dict, set, etc)
