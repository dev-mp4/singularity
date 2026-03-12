mod core;
mod util;
mod renderer;

use gl;

use core::window;
use renderer::opengl::opengl;
use util::msgbox;
use std::process;
use renderer::renderer::Renderer;

fn main() {
    let mut window = window::Window::new(1280, 720, "Hello, Rust!").unwrap_or_else(|_| {
        msgbox::msg_error("Error", "Failed to init window!");

        process::exit(1);
    });

    opengl::OpenGL::init(&mut window).unwrap_or_else(|_| {
        msgbox::msg_error("Error", "Failed to init OpenGL!");

        process::exit(1);
    });

    while !window.should_close() {
        opengl::OpenGL::clear(255, 255, 255);

        window.update();
    }
}