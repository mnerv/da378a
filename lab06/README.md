# cat language

Mini project.

## Requirements

  - [cmake](https://cmake.org)
  - [vcpkg](http://vcpkg.io) - Google Test

[vcpkg](http://vcpkg.io) is not required.

## Build

This project requires `vcpkg` to run unit tests, but it can run without the test suites. Use `cmake` with
`-DCMAKE_TOOLCHAIN_FILE`flag as the command below to enable test targets.

```
cmake -S . -Bbuild -GNinja -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
```

`${VCPKG_ROOT}`: This points to where the `vcpkg` located on your system.

## Grammar

```
S: Statement
E: Rule (Expression)
T: Non-Terminal Symbols "Grammar Symbols" (Term)
F: (Factor)
+-*/()=: Terminal Symbols
```

```
S     -> ID [ ID | E ]+
S     -> ID = [ E | ID ]
E     -> T [ + | - T ]+
T     -> F [ * | / T ]+
F     -> ID | INT | FLOAT | (E) | -F
ID    -> ^[a-zA-Z][a-zA-Z0-9_]*$
INT   -> ^[-+]?[0-9]+$
FLOAT -> ^[-+]?[0-9]+.[0-9]*f?$
```

`ID`, `INT`, and `FLOAT` rule is a valid regex.

## Usage

This project include two tests files, `hello.cat` and `hello_extend.cat` in `tests` directory.

