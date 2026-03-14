use crate::types::image::Image;

pub trait Texture {
    fn load(image: &Image) -> Self;
    fn delete(&self);
    fn bind(&self);
    fn unbind(&self);
}