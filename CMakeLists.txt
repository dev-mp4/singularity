cmake_minimum_required(VERSION 4.0)

project(singularity)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL_TESTS OFF CACHE INTERNAL "")
set(SDL_EXAMPLES OFF CACHE INTERNAL "")

set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.4.12
)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.3
)

FetchContent_MakeAvailable(SDL3)
FetchContent_MakeAvailable(glm)

add_library(glad
    glad/src/glad.c
)
target_include_directories(glad PUBLIC glad/include)

set_target_properties(glad PROPERTIES
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
)

add_executable(singularity
    src/main.cpp
    src/logger/logger.cpp
    src/render/renderer.cpp
    src/render/opengl/glrenderer.cpp
    src/render/opengl/glshader.cpp
    src/render/opengl/glmesh.cpp
    src/window/window.cpp
    src/window/windowevent.cpp
    src/core/input.cpp
    src/core/engine.cpp
    src/core/gameobject.cpp
    src/core/scene.cpp
    src/core/graphics/mesh.cpp
    src/core/graphics/shader.cpp
    src/core/graphics/shadermanager.cpp
    src/core/components/transform.cpp
    src/core/components/meshrenderer.cpp
    src/core/time.cpp
    src/core/material.cpp
)

target_link_libraries(singularity PUBLIC glad)
target_link_libraries(singularity PUBLIC SDL3::SDL3)
target_link_libraries(singularity PUBLIC glm::glm)

target_include_directories(singularity PUBLIC src)

if(WIN32)    
    # copy SDL3.dll
    add_custom_command(TARGET singularity POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE_DIR:singularity>
    )
endif()

set_target_properties(singularity PROPERTIES EXPORT_COMPILE_COMMANDS ON)