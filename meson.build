project('singularity', ['c', 'cpp'], version: 'dev', default_options: ['warning_level=3', 'cpp_std=c++20'])

srcs = [
    'src/main.cpp',
    'src/core/window.cpp',
    'src/renderer/opengl/opengl.cpp',
    'src/renderer/opengl/shader.cpp',
    'src/renderer/opengl/mesh.cpp',
    'src/renderer/opengl/texture.cpp',
    'src/loader/png.cpp',
    'src/core/engine.cpp',
    'src/logger/logger.cpp',
    
    'src/library/systems/camerasystem.cpp',
    'src/library/systems/entitymeshrenderer.cpp',
    'src/library/systems/transformsystem.cpp'
]

glad_inc = include_directories('glad/include')
glad_lib = static_library(
    'glad',
    'glad/src/glad.c',
    include_directories: glad_inc,
)

glfw_dep = dependency('glfw3', required: true)
spng_dep = dependency('spng', required: true)

if not spng_dep.found()
  spng_dep = dependency('libspng', required: true)
endif

flecs_proj = subproject('flecs')
flecs_dep = flecs_proj.get_variable('flecs_dep')

glm_dep = dependency('glm', required: true)

cpp = meson.get_compiler('cpp')

if host_machine.system() == 'windows'
    if cpp.get_id() != 'msvc'
        error('Only MSVC is supported!')
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
endif

executable(
    'singularity',
    srcs,
    dependencies: [glfw_dep, spng_dep, flecs_dep,],
    link_with: [glad_lib],
    include_directories: [glad_inc, include_directories('src')],
    override_options : ['cpp_std=c++20']
)