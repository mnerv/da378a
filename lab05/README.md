# string

A naive and simple string class that only handles 8-bit chars.

## Requirements

  - [cmake](https://cmake.org)
  - [vcpkg](http://vcpkg.io)

## Build

To build this project it is recommended to use `cmake` and `vcpkg` together. The
project uses Google Test library for running the unit tests. This is not
required if only `maintest` is the only requirement.

Usage with `vcpkg` with command below. Omit the `-DCMAKE_TOOLCHAIN_FILE` flag to
disable it.

```
cmake -S . -Bbuild -GNinja -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
```

`${VCPKG_ROOT}`: This points to where the `vcpkg` located on your system.

