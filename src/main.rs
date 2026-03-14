mod core;
mod util;
mod render;
mod types;
mod loader;

use core::window;
use util::msgbox;
use loader::png;
use render::opengl;
use render::renderer::Renderer;
use render::shader::Shader;
use render::mesh::Mesh;
use render::texture::Texture;
use std::fs;
use std::process;

fn main() {
    let mut window = window::Window::new(1280, 720, "Hello, Rust!").unwrap_or_else(|_| {
        msgbox::msg_error("Error", "Failed to init window!");

        process::exit(1);
    });

    opengl::opengl::OpenGL::init(&mut window).unwrap_or_else(|_| {
        msgbox::msg_error("Error", "Failed to init OpenGL!");

        process::exit(1);
    });

    let vertex_shader = fs::read_to_string("res/vertex.glsl").unwrap_or_else(|_| {
        msgbox::msg_error("Error", "Failed to read vertex shader!");

        process::exit(1);
    });

    let fragment_shader = fs::read_to_string("res/fragment.glsl").unwrap_or_else(|_| {
        msgbox::msg_error("Error", "Failed to read fragment shader!");

        process::exit(1);
    });

    let shader = opengl::shader::Shader::fromGLSL(vertex_shader.as_str(), fragment_shader.as_str()).unwrap_or_else(|err| {
        match err {
            opengl::shader::GLSLError::VertexCompileError(str) => {
                msgbox::msg_error("Error", format!("Failed to compile vertex shader: {}", str).as_str());
                process::exit(1);
            },
            opengl::shader::GLSLError::FragmentCompileError(str) => {
                msgbox::msg_error("Error", format!("Failed to compile fragment shader: {}", str).as_str());
                process::exit(1);
            },
            opengl::shader::GLSLError::LinkError(str) => {
                msgbox::msg_error("Error", format!("Failed to link shader program: {}", str).as_str());
                process::exit(1);
            }
        }
    });

    let vertices: Vec<f32> = vec![
        -0.5, -0.5, 0.0, 0.0, 0.0,
        0.5, -0.5, 0.0, 1.0, 0.0,
        0.0, 0.5, 0.0, 0.5, 1.0,
    ];

    let indices: Vec<u32> = vec![
        0, 1, 2
    ];

    let mesh = opengl::mesh::Mesh::new(&vertices, &indices, &vec![3, 2]);

    let test_image = png::load_png("res/test.png").unwrap_or_else(|_| {
        msgbox::msg_error("Error", "Failed to load image!");

        process::exit(1);
    });

    let texture = opengl::texture::Texture::load(&test_image);

    while !window.should_close() {
        opengl::opengl::OpenGL::clear(255, 255, 255);

        shader.attach();
        texture.bind();
        mesh.draw();

        window.update();
    }

    shader.delete();
    mesh.delete();
    texture.delete();
}