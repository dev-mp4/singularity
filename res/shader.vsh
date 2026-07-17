#version 440 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vUV;

uniform mat4 vModelMatrix;

out vec2 fUV;

void main() {
    fUV = vUV;
    gl_Position = vModelMatrix * vec4(vPos, 1.0);
}