use glam::Mat4;

pub trait Shader {
    fn delete(&self);
    fn attach(&self);
    fn detach(&self);
    fn uniform_matrix4f(&self, name: &str, matrix: &Mat4);
}