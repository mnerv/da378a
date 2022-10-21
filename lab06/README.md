# cat language

Mini project.

## Requirements

  - [cmake](https://cmake.org)
  - [vcpkg](http://vcpkg.io) - Google Test

[vcpkg](http://vcpkg.io) is not required if you're not running unit tests. By default, if GTest library is not found,
test targets are not generated.

## Build

If you have `vcpkg` installed then you can use the command below for unix systems. This will automatically install
Google Test library. To use without Google Test run `cmake` without `-DCMAKE_TOOLCHAIN_FILE` argument.

```
cmake -S . -Bbuild -GNinja -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
```

`${VCPKG_ROOT}`: This points to where the `vcpkg` located on your system.
