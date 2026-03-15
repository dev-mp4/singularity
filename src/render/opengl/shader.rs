use std::ffi::{CString, CStr};
use crate::render::shader;
use gl;
use glam::Mat4;

pub struct Shader {
    id: u32
}

pub enum GLSLError {
    VertexCompileError(String),
    FragmentCompileError(String),
    LinkError(String)
}

impl shader::Shader for Shader {
    fn delete(&self) {
        unsafe {
            gl::DeleteShader(self.id);
        }
    }

    fn attach(&self) {
        unsafe {
            gl::UseProgram(self.id);
        }
    }

    fn detach(&self) {
        unsafe {
            gl::UseProgram(0);
        }
    }

    fn uniform_matrix4f(&self, name: &str, matrix: &Mat4) {
        unsafe {
            let location = gl::GetUniformLocation(self.id, CString::new(name).unwrap().as_ptr());
            if location < 0 {
                return;
            }
            gl::UniformMatrix4fv(location, 1, gl::FALSE, matrix.to_cols_array().as_ptr());
        }
    }
}

impl Shader {
    pub fn new(id: u32) -> Self {
        Self {
            id
        }
    }

    pub fn from_glsl(vertex_code: &str, fragment_code: &str) -> Result<Self, GLSLError> {
        unsafe {
            let v_raw_code = CString::new(vertex_code).unwrap();
            let f_raw_code = CString::new(fragment_code).unwrap();

            let mut success = 0;
            let mut log: [i8; 512] = [0; 512];

            let vertex_shader = gl::CreateShader(gl::VERTEX_SHADER);
            gl::ShaderSource(vertex_shader, 1, &v_raw_code.as_ptr(), std::ptr::null());
            gl::CompileShader(vertex_shader);
            gl::GetShaderiv(vertex_shader, gl::COMPILE_STATUS, &mut success);
            if success == 0 {
                gl::GetShaderInfoLog(vertex_shader, 512, std::ptr::null_mut(), log.as_mut_ptr() as *mut i8);
                gl::DeleteShader(vertex_shader);
                let error = unsafe {
                    CStr::from_ptr(log.as_ptr())
                }
                    .to_string_lossy()
                    .into_owned();
                return Err(GLSLError::VertexCompileError(error));
            }

            let fragment_shader = gl::CreateShader(gl::FRAGMENT_SHADER);
            gl::ShaderSource(fragment_shader, 1, &f_raw_code.as_ptr(), std::ptr::null());
            gl::CompileShader(fragment_shader);
            gl::GetShaderiv(fragment_shader, gl::COMPILE_STATUS, &mut success);
            if success == 0 {
                gl::GetShaderInfoLog(fragment_shader, 512, std::ptr::null_mut(), log.as_mut_ptr() as *mut i8);
                gl::DeleteShader(vertex_shader);
                gl::DeleteShader(fragment_shader);
                let error = unsafe {
                    CStr::from_ptr(log.as_ptr())
                }
                    .to_string_lossy()
                    .into_owned();
                return Err(GLSLError::FragmentCompileError(error));
            }

            let program = gl::CreateProgram();
            gl::AttachShader(program, vertex_shader);
            gl::AttachShader(program, fragment_shader);
            gl::LinkProgram(program);

            gl::GetProgramiv(program, gl::LINK_STATUS, &mut success);
            if success == 0 {
                gl::GetProgramInfoLog(program, 512, std::ptr::null_mut(), log.as_mut_ptr() as *mut i8);
                gl::DeleteShader(vertex_shader);
                gl::DeleteShader(fragment_shader);
                gl::DeleteProgram(program);
                let error = unsafe {
                    CStr::from_ptr(log.as_ptr())
                }
                    .to_string_lossy()
                    .into_owned();
                return Err(GLSLError::LinkError(error));
            }

            gl::DeleteShader(vertex_shader);
            gl::DeleteShader(fragment_shader);

            Ok(Self::new(program))
        }
    }
}