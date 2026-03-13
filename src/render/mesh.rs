pub trait Mesh {
    fn new(vertices: &Vec<f32>, indices: &Vec<u32>, attributes: &Vec<u8>) -> Self;
    fn delete(&self);
    fn draw(&self);
}