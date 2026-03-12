use crate::core::window;
use crate::render::renderer;
use gl;

pub struct OpenGL {}

impl renderer::Renderer for OpenGL {
    fn init(window: &mut window::Window) -> Result<(), ()> {
        let mut failed = false;

        gl::load_with(|s| {
            match window.get_proc_address(s) {
                Ok(ptr) => ptr,
                Err(_) => {
                    failed = true;
                    std::ptr::null()
                }
            }
        });

        if failed {
            Err(())
        } else {
            Ok(())
        }
    }

    fn clear(r: u8, g: u8, b: u8) {
        unsafe {
            gl::ClearColor(r as f32, g as f32, b as f32, 255.0);
            gl::Clear(gl::COLOR_BUFFER_BIT);
        }
    }
}