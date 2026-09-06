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

> [!NOTE]
> If you want to modify engine's source code and you use MSVC and C++ LSP that require compilation database(a.k.a. `compile_commands.json`),  
> clangd for example, you'll have to use Ninja generator, because MSBuild doesn't support generating compilation database.  
> Install `ninja`, open VS Developer console and run bootstrap here, but add `-G Ninja` to bootstrap command.

## Usage

While engine is still under active development, you can just compile and run test scene.

## Features

Engine has Unity-like architecture, built-in ImGui support, developer UI(press F12 to open it), Java-like [event bus](https://github.com/hexx1edev/EventBus).
Planned features are:  
- [x] Event bus
- [ ] Performance profiler
- [ ] Fully customizable render pipeline

## License

The engine is licensed under [LGPL-3.0](LICENSE.txt). Feel free to use it in any kind of project and contribute!