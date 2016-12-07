# fs - Portable filesystem operations

A thin wrapper to unify some of the file system operations that can be
accomplished in C.

## Getting Started

### Copy Pasta

Copy the files in the `src` directory and `include` directory to your project
and compile them. Note: inside of `src` there resides 3 directories. One is
windows specific the other is posix specific.

### CMake

You should be able to use this as a git submodule and use CMake and do the
following:

```cmake
add_subdirectory(fs)
```
