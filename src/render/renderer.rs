use crate::core::window;

pub trait Renderer {
    fn init(window: &mut window::Window) -> Result<(), ()>;
    fn clear(r: u8, g: u8, b: u8);
}