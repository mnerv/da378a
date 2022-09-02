# Computer Science: C++ and Program Construction

This repository holds all the course labs. It includes 6 programming assignments (Labs). Each labs has its own tasks to implement.

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

