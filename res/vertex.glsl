#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;

out vec2 _fragUV;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = proj * view * model * vec4(pos.x, pos.y, pos.z, 1.0);
    _fragUV = uv;
}