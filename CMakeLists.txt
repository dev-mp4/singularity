cmake_minimum_required(VERSION 4.0)

project(singularity C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Skip install rules for fetched projects to avoid export target errors
set(CMAKE_SKIP_INSTALL_RULES ON CACHE BOOL "" FORCE)

# Build fetched dependencies as dynamic libraries
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)

# Disable tests & example executables to prevent target collisions (e.g. 'example')
set(SDL_TESTS OFF CACHE INTERNAL "")
set(SDL_EXAMPLES OFF CACHE INTERNAL "")
set(ZLIB_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SPNG_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

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
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.92.8
)
FetchContent_Declare(
    EventBus
    GIT_REPOSITORY https://github.com/hexx1edev/EventBus.git
    GIT_TAG        1.0.0
)
FetchContent_Declare(
    zlib
    GIT_REPOSITORY https://github.com/madler/zlib.git
    GIT_TAG        v1.3.1
)
FetchContent_Declare(
    spng
    GIT_REPOSITORY https://github.com/randy408/libspng.git
    GIT_TAG        v0.7.4
)

FetchContent_MakeAvailable(SDL3)
FetchContent_MakeAvailable(glm)
FetchContent_MakeAvailable(imgui)
FetchContent_MakeAvailable(EventBus)

# --- ZLIB SETUP ---
FetchContent_MakeAvailable(zlib)

if(NOT TARGET ZLIB::ZLIB)
    if(TARGET zlib)
        add_library(ZLIB::ZLIB ALIAS zlib)
    elseif(TARGET zlibstatic)
        add_library(ZLIB::ZLIB ALIAS zlibstatic)
    endif()
endif()

set(ZLIB_FOUND TRUE CACHE BOOL "" FORCE)
set(ZLIB_INCLUDE_DIR "${zlib_SOURCE_DIR};${zlib_BINARY_DIR}" CACHE PATH "" FORCE)
set(ZLIB_INCLUDE_DIRS "${zlib_SOURCE_DIR};${zlib_BINARY_DIR}" CACHE PATH "" FORCE)
set(ZLIB_LIBRARY ZLIB::ZLIB CACHE STRING "" FORCE)
set(ZLIB_LIBRARIES ZLIB::ZLIB CACHE STRING "" FORCE)

# --- SPNG SETUP ---
FetchContent_MakeAvailable(spng)

# GLAD
add_library(glad SHARED
    glad/src/glad.c
)
target_include_directories(glad PUBLIC glad/include)

set_target_properties(glad PROPERTIES
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
)

# ImGui (Reverted back to original static target setup)
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC 
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui PUBLIC SDL3::SDL3)

file(GLOB_RECURSE SINGULARITY_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)

add_executable(singularity ${SINGULARITY_SOURCES})

target_link_libraries(singularity PUBLIC 
    glad 
    SDL3::SDL3 
    glm::glm 
    EventBus::EventBus 
    imgui 
    spng
)

target_include_directories(singularity PUBLIC src)

if(WIN32)    
    # Copy shared library DLLs next to singularity.exe
    add_custom_command(TARGET singularity POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3::SDL3>
            $<TARGET_FILE:glad>
            $<TARGET_FILE:spng>
            $<TARGET_FILE:zlib>
            $<TARGET_FILE_DIR:singularity>
    )
endif()

# remove RTTI, because it's bad
if(MSVC)
    string(REPLACE "/GR" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    add_compile_options(/GR-)
else()
    add_compile_options(-fno-rtti)
endif()

set_target_properties(singularity PROPERTIES EXPORT_COMPILE_COMMANDS ON)

add_compile_definitions(SINGULARITY_DEV_BUILD)