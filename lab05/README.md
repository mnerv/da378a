# string

A naive and simple string class that only handles 8-bit chars.

## Requirements

  - [cmake](https://cmake.org)
  - [vcpkg](http://vcpkg.io)

## Build

To build this project it is recommended to use `cmake` and `vcpkg` together. The
project uses Google Test library for running the unit test and you need it to
installed on your library so cmake can find it using its `find_package`
function.

But if you're using `vcpkg` then you can run the following command and it'll
install **GTest** library for you on the project level.

```
cmake -S . -Bbuild -GNinja -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
```

`${VCPKG_ROOT}`: This points to where the `vcpkg` located on your system.

If you want to install vcpkg then follow their
[Get started](https://vcpkg.io/en/getting-started.html) guide.

**Note**: The project can be run standalone too without Google Test and there will
only be one executable that's runnable.

