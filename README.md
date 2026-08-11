# Singularity

A simple and fast 3D engine, written in С++

## Building

### Linux/UNIX

Make sure that `C++ compiler, cmake, make(or ninja)` is installed.  
Run `cmake -S . -B build` to bootstrap project and download dependencies.  
Run `cmake --build build` to compile dependencies and project.

### Windows

Currently, I tested engine with MSVC only, install MSVC(or simply Visual Studio with MSVC enabled) and CMake.  
Run `cmake -S . -B build` to bootstrap project and download dependencies.  
Run `cmake --build build` to compile dependencies and project.

## Usage

While engine is still under active development, you can just compile and run test scene.

## Features

Engine has Unity-like architecture, built-in ImGui support, developer UI(press F12 to open it), planned features are:  
- [ ] Performance profiler
- [ ] Event bus system(just like Java)