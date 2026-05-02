#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;

out vec2 _fraguv;

uniform mat4 model;
uniform mat4 projview;

void main()
{
    _fraguv = uv;
    gl_Position = projview * model * vec4(pos, 1.0);
}