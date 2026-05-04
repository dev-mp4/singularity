project('singularity', ['c', 'cpp'], license: 'lgpl', version: '1.0-dev', default_options: ['warning_level=3'])

srcs = [
    'src/core/window.cpp',
    'src/renderer/opengl/opengl.cpp',
    'src/renderer/opengl/shader.cpp',
    'src/renderer/opengl/mesh.cpp',
    'src/renderer/opengl/texture.cpp',
    'src/loader/png.cpp',
    'src/core/engine.cpp',
    'src/logger/logger.cpp',
    'src/core/input.cpp',
    
    'src/library/systems/camerasystem.cpp',
    'src/library/systems/entitymeshrenderer.cpp',
    'src/library/systems/transformsystem.cpp',
    'src/library/register.cpp'
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

singularity = shared_library(
    'singularity',
    srcs,
    dependencies: [glfw_dep, spng_dep, flecs_dep,],
    link_with: [glad_lib],
    include_directories: [glad_inc, include_directories('src')],
    install: true
)