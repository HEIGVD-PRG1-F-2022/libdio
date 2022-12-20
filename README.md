# libdio

Input / Output library for the PRG1F course

## Usage

To use this library in your code, you have to add the following lines in your `CMakeLists.txt`:

```cmake
include(FetchContent) # once in the project to include the module

FetchContent_Declare(libdio
        GIT_REPOSITORY https://github.com/HEIGVD-PRG1-F-2022/libdio.git
        GIT_TAG v0.2.4
        )
FetchContent_MakeAvailable(libdio)

# Here are your other declarations, like `add_executable`

# Replace `PROJECT` with the name of your executable
target_link_libraries(PROJECT PRIVATE libdio)
```

Now you can do the following to include the library in your files:

```c++
#include <libdio/display.h>
#include <libdio/input.h>
```

## Changelog

2022-12-14 - 0.2.3
  * adds `cursorHome`, `cursorVisible`, and `cursorDelete` to `DString`
  * adds `cursor{Back,Forward,Up,Down,Position,{Next,Previous}Line,HorizontalAbsolute}`
  * overloads `append` to return a reference to `DString`
  * refactoring CSI string
  * adds `<<(char)`
  * move `CHANGELOG.md` to `README.md`

2022-11-30 - v0.2
  * Rewrite of display

2022-11-23 - v0.1
  * Initial commit
  * Made by Florian Duruz and Aellen Quentin for the course PRG1-f at HEIG/VD - https://heig-vd.ch/

## Examples

There is an example here: [example](example/main.cpp).

## Develop libdio locally

If you want to change how `libdio` works in your local directory, you can do the following:

1. Clone the libdio repo locally
2. Change the code for `CMakeLists.txt` to the following:

```cmake
add_subdirectory(libdio)
# Here are your other declarations, like `add_executable`

# Replace `PROJECT` with the name of your executable
target_link_libraries(PROJECT PRIVATE libdio)
```

Please don't forget to create a pull-request with your changes!

## Images

(Les images ont été prises durant la beta et ne sont pas représentatives du produit final)

![image](https://user-images.githubusercontent.com/46396184/202451747-80dc852e-b7df-4511-9a0b-6907789343b7.png)

![image](https://user-images.githubusercontent.com/46396184/202451486-d65ad651-b26e-4ddf-8b79-2c10e40fdb47.png)
