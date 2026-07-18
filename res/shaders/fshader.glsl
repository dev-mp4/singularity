#version 440 core

in vec2 fUV;

out vec4 fColor;

void main() {
    fColor = vec4(fUV, 1.0, 1.0);
}