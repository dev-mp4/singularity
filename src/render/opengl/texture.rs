use crate::render::texture;
use crate::types::image::Image;
use gl;

pub struct Texture {
    id: u32
}

impl Texture {
    pub fn new(id: u32) -> Self {
        Self { id }
    }
}

impl texture::Texture for Texture {
    fn load(image: &Image) -> Self {
        unsafe {
            let mut texture: u32 = 0;

            gl::GenTextures(1, &mut texture);
            gl::BindTexture(gl::TEXTURE_2D, texture);

            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::REPEAT as i32);
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::REPEAT as i32);

            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::NEAREST as i32);
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::NEAREST as i32);

            gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGBA as i32, image.width as i32, image.height as i32, 0, gl::RGBA, gl::UNSIGNED_BYTE, image.data.as_ptr() as *const gl::types::GLvoid);
            gl::GenerateMipmap(gl::TEXTURE_2D);
            
            gl::BindTexture(gl::TEXTURE_2D, 0);

            Texture::new(texture)
        }
    }
    
    fn delete(&self) {
        unsafe {
            gl::DeleteTextures(1, &self.id);
        }
    }
    
    fn bind(&self) {
        unsafe {
            gl::BindTexture(gl::TEXTURE_2D, self.id);
        }
    }
    
    fn unbind(&self) {
        unsafe {
            gl::BindTexture(gl::TEXTURE_2D, 0);
        }
    }
}