project('singularity', ['c', 'cpp'], version: 'dev')

srcs = [
    'src/main.cpp',
    'src/core/window.cpp',
    'src/renderer/opengl/opengl.cpp',
    'src/renderer/opengl/shader.cpp',
    'src/renderer/opengl/mesh.cpp',
    'src/renderer/opengl/texture.cpp',
    'src/loader/png.cpp',
    'src/core/ecs/componentregistry.cpp',
    'src/core/ecs/entitymanager.cpp',
    'src/core/engine.cpp',
    'src/core/scene.cpp',
    'src/core/ecs/systemregistry.cpp'
]

glad_inc = include_directories('glad/include')
glad_lib = static_library(
    'glad',
    'glad/src/glad.c',
    include_directories: glad_inc,
)

glfw_dep = dependency('glfw3')
spng_dep = dependency('spng', required: false)

if not spng_dep.found()
  spng_dep = dependency('libspng', required: true)
endif

cpp = meson.get_compiler('cpp')

if host_machine.system() == 'windows'
    if cpp.get_id() != 'msvc'
        error('Only MSVC is supported, use MSVC version that supports C++23 preview')
    endif

    configure_file(
        input: join_paths(meson.current_build_dir(), 'subprojects', 'glfw-3.4', 'glfw3-3.dll'),
        output: 'glfw3-3.dll',
        copy: true
    )

    configure_file(
        input: join_paths(meson.current_build_dir(), 'subprojects', 'libspng-0.7.4', 'spng-0.dll'),
        output: 'spng-0.dll',
        copy: true
    )

    configure_file(
        input: join_paths(meson.current_build_dir(), 'subprojects', 'zlib-1.2.13', 'z.dll'),
        output: 'z.dll',
        copy: true
    )

    compiler_args = ['/std:c++latest']
else
    compiler_args = ['-std=c++23']
endif

executable(
    'singularity',
    srcs,
    dependencies: [glfw_dep, spng_dep],
    link_with: [glad_lib],
    include_directories: [glad_inc, include_directories('src')],
    cpp_args: compiler_args
)