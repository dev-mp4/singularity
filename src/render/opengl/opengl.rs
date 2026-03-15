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
            unsafe {
                gl::Enable(gl::BLEND);
                gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);

                gl::Enable(gl::DEPTH_TEST);
            }

            Ok(())
        }
    }

    fn clear(r: u8, g: u8, b: u8) {
        unsafe {
            gl::ClearColor(r as f32, g as f32, b as f32, 255.0);
            gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
        }
    }
}