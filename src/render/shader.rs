pub trait Shader {
    fn delete(&self);
    fn attach(&self);
    fn detach(&self);
}