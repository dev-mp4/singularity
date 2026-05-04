# Singularity

A simple and fast ECS 3D engine, written in С++

## Building SDK

To make an application using Singularity, you need an SDK.

### Linux/UNIX

Make sure that `C++ compiler, python3, meson, ninja, patchelf` is installed.  
Run `python3 gen_sdk.py <SDK output directory>`, full SDK will be available in specified directory.  

## Usage

Just put SDK into your project, add it as subdir and get `singularity_dep` variable, add it as a dependency to your executable.

## What's next?

Currently, I am writing a documentation and a beginner-friendly usage tutorial, but engine is already (technically) complete!  
The only missing features are:
 - Per-camera framebuffers
 - Multipass rendering with post-processing
 - Forward and deffered lighting
 - Physics engine