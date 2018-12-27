# Windows Setup with mingw-w64/CMake/VSCode

## Installation

### Install mingw-w64

Download from here:
https://mingw-w64.org/doku.php/download

Install and make sure to add the `bin` directory to `PATH`.

For packages with an installer program it may be cleaner to install, copy the directory from `Program Files` to a shorter path like `C:/mingw-w64`, then uninstall.

### Download SDL2

Download the `mingw` package from here:
https://www.libsdl.org/download-2.0.php

Extract it to: `C:/SDL2-mingw` (replace with your own preference).

### Install CMake

Download ZIP package from here:
https://cmake.org/download/

Extract to `C:/CMake` and add `C:/CMake/bin` to `PATH`.

### Install VSCode

Download 64-bit ZIP package from here:
https://code.visualstudio.com/download

Extract to `C:/VSCode` and add it to `PATH`.

Note that the `bin` subdirectory doens't have the actual VSCode executable but a batch file shortcut.

Run VSCode now and install the following extensions:

1. C/C++ by Microsoft
2. CMake Tools
3. CMake (for syntax highlighting)

Note that the C/C++ and CMake extensions should be able to find the toolchains automatically as long as they've been added to `PATH`.

### Add CMake config for SDL2

Add a `sdl2-config.cmake` file to `C:/SDL2-devel-mingw` with the following contents:
```cmake
# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  set(SDL2_ROOT "${CMAKE_CURRENT_LIST_DIR}/x86_64-w64-mingw32")
else()
  set(SDL2_ROOT "${CMAKE_CURRENT_LIST_DIR}/i686-w64-mingw32")
endif()

set(SDL2_INCLUDE_DIRS "${SDL2_ROOT}/include/SDL2")
set(SDL2_LIBDIR "${SDL2_ROOT}/lib")
set(SDL2_LIBRARIES "-L${SDL2_LIBDIR} -lmingw32 -lSDL2main -lSDL2 -mwindows")

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
```

## VSCode Configuration

Run VSCode and select "File -> Open Folder" to open the `SDLTest` directory.

Select the compiler "Kit" for CMake (e.g. `GCC 8.1.0`).

Open the `settings.json` file and add `SDL2_DIR` variable to CMake configuration so it can find the SDL2 package:
```json
    "cmake.configureSettings": {
        "SDL2_DIR": "C:/SDL2-devel-mingw"
    }
```

## Copy SDL2.dll to the build directory

The DLL file can be found here: `C:/SDL2-devel-mingw/x86_64-w64-mingw32/bin/SDL.dll`.

Copy it to the SDLTest project's `build` directory.

## Building

Press F7 to make a build.

More specific commands could be used to trigger various parts of the build process:

* "CMake: Configure" - to generate makefiles
* "CMake: Delete cached settings and reconfigure"
* "CMake: Clean rebuild"
* "CMake: Build" - regular incremental build

## Running

Select "Debug -> Add Configuration" to add a launch configuration.

Select "C/C++: (Windows) Launch" and specify the path to the target executable in `launch.json`:
```json
"program": "${workspaceFolder}/build/SDLTest.exe"
```

Note that the CMake extension supports a built-in `Shift-F5` launch command ("Execute the current target without a debugger") but it didn't seem to work on my system.

## Debugging

Add a launch configuration "C/C++: (gdb) Launch" and specify `program` and `miDebuggerPath` elements in `launch.json`:
```json
"program": "${workspaceFolder}/build/SDLTest.exe",
"miDebuggerPath": "C:/SDL2-devel-mingw/bin/gdb.exe"
```

(No idea why this is not populated automatically by C/C++ extension.)

You can also use the built-in CMake `Ctrl-F5` command ("Debug the target") but with no ability to specify extra command line arguments, environment, etc.
