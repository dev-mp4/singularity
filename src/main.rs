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
use glam::{Mat4, Vec3, Quat};

fn main() {
    let mut window = window::Window::new(1280, 720, "Singularity").unwrap_or_else(|_| {
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

    let shader = opengl::shader::Shader::from_glsl(vertex_shader.as_str(), fragment_shader.as_str()).unwrap_or_else(|err| {
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
        // Front face (z=1)
        0.0, 0.0, 1.0, 0.0, 0.0, // bottom-left
        1.0, 0.0, 1.0, 1.0, 0.0, // bottom-right
        1.0, 1.0, 1.0, 1.0, 1.0, // top-right
        0.0, 1.0, 1.0, 0.0, 1.0, // top-left

        // Back face (z=0)
        1.0, 0.0, 0.0, 0.0, 0.0, // bottom-left
        0.0, 0.0, 0.0, 1.0, 0.0, // bottom-right
        0.0, 1.0, 0.0, 1.0, 1.0, // top-right
        1.0, 1.0, 0.0, 0.0, 1.0, // top-left

        // Left face (x=0)
        0.0, 0.0, 0.0, 0.0, 0.0, // bottom-left
        0.0, 0.0, 1.0, 1.0, 0.0, // bottom-right
        0.0, 1.0, 1.0, 1.0, 1.0, // top-right
        0.0, 1.0, 0.0, 0.0, 1.0, // top-left

        // Right face (x=1)
        1.0, 0.0, 1.0, 0.0, 0.0, // bottom-left
        1.0, 0.0, 0.0, 1.0, 0.0, // bottom-right
        1.0, 1.0, 0.0, 1.0, 1.0, // top-right
        1.0, 1.0, 1.0, 0.0, 1.0, // top-left

        // Top face (y=1)
        0.0, 1.0, 1.0, 0.0, 0.0, // bottom-left
        1.0, 1.0, 1.0, 1.0, 0.0, // bottom-right
        1.0, 1.0, 0.0, 1.0, 1.0, // top-right
        0.0, 1.0, 0.0, 0.0, 1.0, // top-left

        // Bottom face (y=0)
        0.0, 0.0, 0.0, 0.0, 0.0, // bottom-left
        1.0, 0.0, 0.0, 1.0, 0.0, // bottom-right
        1.0, 0.0, 1.0, 1.0, 1.0, // top-right
        0.0, 0.0, 1.0, 0.0, 1.0, // top-left
    ];

    let indices: Vec<u32> = vec![
        0, 1, 2, 0, 2, 3,       // Front
        4, 5, 6, 4, 6, 7,       // Back
        8, 9,10, 8,10,11,       // Left
        12,13,14,12,14,15,       // Right
        16,17,18,16,18,19,       // Top
        20,21,22,20,22,23,       // Bottom
    ];

    let mesh = opengl::mesh::Mesh::new(&vertices, &indices, &vec![3, 2]);

    let test_image = png::load_png("res/dirt.png").unwrap_or_else(|_| {
        msgbox::msg_error("Error", "Failed to load image!");

        process::exit(1);
    });

    let texture = opengl::texture::Texture::load(&test_image);

    let perspective = Mat4::perspective_rh_gl(60.0_f32.to_radians(), 1280.0 / 720.0, 0.1, 100.0);
    let view = Mat4::from_translation(Vec3::new(0.0, 0.0, -5.0));
    let mut model: Mat4;

    while !window.should_close() {
        opengl::opengl::OpenGL::clear(255, 255, 255);

        let time = window.get_time() as f32;
        let time_sin = time.sin() as f32;

        model = Mat4::from_rotation_translation(Quat::from_euler(glam::EulerRot::XYZ, time, time, time), Vec3::new(0.0, 0.0, 0.0));

        shader.attach();

        shader.uniform_matrix4f("proj", &perspective);
        shader.uniform_matrix4f("view", &view);
        shader.uniform_matrix4f("model", &model);

        texture.bind();
        mesh.draw();

        window.update();
    }

    shader.delete();
    mesh.delete();
    texture.delete();
}