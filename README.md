# Singularity

A simple and fast ECS 3D engine, written in С++

## Building

### Windows

Make sure that meson, ninja, MSVC and Windows SDK are installed  
Run `bootstrap.bat` file to bootstrap dependencies  
Compile project with meson, all required DLLs will be copied to executable in your build directory automatically.

### Linux or UNIX

Works OOTB, if you're on Void Linux(like me), build and install spng from source by yourself, pkg-config detection works.  
Compile project with meson, you'll find the executable in your build directory

## Usage

The engine is currently not ready for usage and is basically a program, not a library, but the work is going, watch for commits for first release!