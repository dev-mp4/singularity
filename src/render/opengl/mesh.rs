use crate::render::mesh;
use gl;

pub struct Mesh {
    vao: u32,
    vbo: u32,
    ebo: u32,
    index_count: u32
}

impl mesh::Mesh for Mesh {
    fn new(vertices: &Vec<f32>, indices: &Vec<u32>, attributes: &Vec<u8>) -> Self {
        unsafe {
            let mut mesh = Self {
                vao: 0,
                vbo: 0,
                ebo: 0,
                index_count: indices.len() as u32
            };

            gl::GenVertexArrays(1, &mut mesh.vao);
            gl::BindVertexArray(mesh.vao);

            gl::GenBuffers(1, &mut mesh.vbo);
            gl::BindBuffer(gl::ARRAY_BUFFER, mesh.vbo);
            gl::BufferData(gl::ARRAY_BUFFER, (vertices.len() * size_of::<f32>()) as gl::types::GLsizeiptr, vertices.as_ptr() as *const gl::types::GLvoid, gl::STATIC_DRAW);

            let total_stride = attributes.iter().sum::<u8>() as u32;

            let mut stride: u32 = 0;
            let mut index: u32 = 0;
            attributes.iter().for_each(|&x| {
                gl::VertexAttribPointer(index, x as gl::types::GLint, gl::FLOAT, gl::FALSE, (total_stride * size_of::<f32>() as u32) as i32, (stride * size_of::<f32>() as u32) as *const gl::types::GLvoid);
                gl::EnableVertexAttribArray(index);
                stride += x as u32;
                index += 1;
            });

            gl::GenBuffers(1, &mut mesh.ebo);
            gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, mesh.ebo);
            gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, (indices.len() * size_of::<u32>()) as gl::types::GLsizeiptr, indices.as_ptr() as *const gl::types::GLvoid, gl::STATIC_DRAW);

            gl::BindVertexArray(0);

            mesh
        }
    }

    fn delete(&self) {
        unsafe {
            gl::DeleteVertexArrays(1, &self.vao);
            gl::DeleteBuffers(1, &self.vbo);
            gl::DeleteBuffers(1, &self.ebo);
        }
    }

    fn draw(&self) {
        unsafe {
            gl::BindVertexArray(self.vao);
            gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, self.ebo);
            gl::DrawElements(gl::TRIANGLES, self.index_count as gl::types::GLsizei, gl::UNSIGNED_INT, 0 as *const gl::types::GLvoid);
            gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, 0);
            gl::BindVertexArray(0);
        }
    }
}