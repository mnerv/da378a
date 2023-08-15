# Computer Science: C++ and Program Construction

This repository holds all the course labs. It includes 6 programming assignments (Labs). Each labs has its own tasks to implement.

## Resources

  - [cppreference](https://en.cppreference.com/w/)
  - [Fundamental types](https://en.cppreference.com/w/cpp/language/types)
  - [Integer literal](https://en.cppreference.com/w/cpp/language/integer_literal)
  - [Character literal](https://en.cppreference.com/w/cpp/language/character_literal)
  - [Compiler Explorer](https://godbolt.org)

**Fundamental types**: LP-prefix stands for Long Pointer, example: LP64 is long-pointer 64.

## Labs Summary

**lab01** introduces how to get input parameters from the command line and a simple 2nd-degree polynomial program implementation. The second was to introduce us to how to write a C++ class.

**lab02** Task 1 is an implementation of a prime calculation using the Eratosthenes Sieve algorithm. Task 2 is an implementation of string modification using the std::string and then C style with memory allocation.

**lab03** is to create two classes, one that stores the other. The first class is a Person class that has basic information and another is PersonReg which stores these in an array. We also used polymorphism to overload how the Person class should be printed.

**lab04** introduces us to C++ STL, in this case, we use to sort, first to sort integers and then a custom data structure like the Person class from the previous lab03.

**lab05** is a custom string container class that manages its own memory. This also introduces us to copy constructors and what is a good way to grow the memory.

**lab06** is a simple implementation of a custom programming language. Here I've made an AST and an interpreter that can parse the tree.

## Development

### CMake

Generate `ninja` build script using `cmake`.

```
cmake -S . -B build -GNinja
```

Compile with `ninja`.

```
ninja -C build
```

### nvim

Some tasks requires you to compile the file with command line tools and when using neovim with ccls language server it can't know what C++ standard we should be using or what warning flags should be use.

Create `.ccls` file in the project directory and populate it

```
%c++ -std=c++20 -Wall -Wextra -Wconversion -Wpedantic -Wshadow -Werror
```

`%c++`: This depends entirely on what compiler we're using, this can be `g++` or `clang++`

When using `cmake` the configuration will generate `compile_commands.json` file which `ccls` needs to know where it is to setup the LSP server. Symlink it using `ln`

```
ln -sfn build/compile_commands.json .
```

## git

Use `git archive` to create a zip file.

```
git archive --format=zip HEAD:{directory} -o {output}.zip
```

`HEAD:{directory}`: This can be short to just `HEAD` to create a zip from the whole repo.

`{directory}`: Is the directory you want to create a zip file from, example: `lab01`.

`{output}.zip`: Output file path, example: `~/Downloads/lab01.zip`

