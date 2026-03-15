use std::os::raw::c_void;
use glfw::{Context};

pub struct Window {
    pub width: u32,
    pub height: u32,
    window: glfw::PWindow,
    events: glfw::GlfwReceiver<(f64, glfw::WindowEvent)>,
    glfw: glfw::Glfw
}

impl Window {
    pub fn new(width: u32, height: u32, title: &str) -> Result<Self, ()> {
        use glfw::fail_on_errors;
        let mut glfw = glfw::init(fail_on_errors!()).map_err(|_| ())?;
        let (mut window, events) = glfw.create_window(width, height, title, glfw::WindowMode::Windowed).ok_or(())?;
        
        window.make_current();
        window.set_all_polling(true);

        Ok(Self {
            width,
            height,
            window,
            events,
            glfw
        })
    }


    pub fn get_proc_address(&mut self, name: &str) -> Result<*const c_void, ()> {
        self.window.get_proc_address(name).map(|p| p as *const c_void).ok_or(())
    }

    pub fn should_close(&self) -> bool {
        self.window.should_close()
    }

    pub fn update(&mut self) {
        self.glfw.poll_events();
        self.window.swap_buffers();
    }
    
    pub fn get_time(&self) -> f64 {
        self.glfw.get_time()
    }
}