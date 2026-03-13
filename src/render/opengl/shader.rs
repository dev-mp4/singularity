use std::ffi::{CString, CStr};
use crate::render::shader;
use gl;

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
}

impl Shader {
    pub fn new(id: u32) -> Self {
        Self {
            id
        }
    }

    pub fn fromGLSL(vertexCode: &str, fragmentCode: &str) -> Result<Self, GLSLError> {
        unsafe {
            let v_raw_code = CString::new(vertexCode).unwrap();
            let f_raw_code = CString::new(fragmentCode).unwrap();

            let mut success = 0;
            let mut log: [i8; 512] = [0; 512];

            let vertexShader = gl::CreateShader(gl::VERTEX_SHADER);
            gl::ShaderSource(vertexShader, 1, &v_raw_code.as_ptr(), std::ptr::null());
            gl::CompileShader(vertexShader);
            gl::GetShaderiv(vertexShader, gl::COMPILE_STATUS, &mut success);
            if success == 0 {
                gl::GetShaderInfoLog(vertexShader, 512, std::ptr::null_mut(), log.as_mut_ptr() as *mut i8);
                gl::DeleteShader(vertexShader);
                let error = unsafe {
                    CStr::from_ptr(log.as_ptr())
                }
                    .to_string_lossy()
                    .into_owned();
                return Err(GLSLError::VertexCompileError(error));
            }

            let fragmentShader = gl::CreateShader(gl::FRAGMENT_SHADER);
            gl::ShaderSource(fragmentShader, 1, &f_raw_code.as_ptr(), std::ptr::null());
            gl::CompileShader(fragmentShader);
            gl::GetShaderiv(fragmentShader, gl::COMPILE_STATUS, &mut success);
            if success == 0 {
                gl::GetShaderInfoLog(fragmentShader, 512, std::ptr::null_mut(), log.as_mut_ptr() as *mut i8);
                gl::DeleteShader(vertexShader);
                gl::DeleteShader(fragmentShader);
                let error = unsafe {
                    CStr::from_ptr(log.as_ptr())
                }
                    .to_string_lossy()
                    .into_owned();
                return Err(GLSLError::FragmentCompileError(error));
            }

            let program = gl::CreateProgram();
            gl::AttachShader(program, vertexShader);
            gl::AttachShader(program, fragmentShader);
            gl::LinkProgram(program);

            gl::GetProgramiv(program, gl::LINK_STATUS, &mut success);
            if success == 0 {
                gl::GetProgramInfoLog(program, 512, std::ptr::null_mut(), log.as_mut_ptr() as *mut i8);
                gl::DeleteShader(vertexShader);
                gl::DeleteShader(fragmentShader);
                gl::DeleteProgram(program);
                let error = unsafe {
                    CStr::from_ptr(log.as_ptr())
                }
                    .to_string_lossy()
                    .into_owned();
                return Err(GLSLError::LinkError(error));
            }

            gl::DeleteShader(vertexShader);
            gl::DeleteShader(fragmentShader);

            Ok(Self::new(program))
        }
    }
}