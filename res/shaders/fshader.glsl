#version 440 core

in vec2 fUV;

out vec4 fColor;

uniform float light; // value just to test materials

void main() {
    fColor = vec4(fUV, 1.0, 1.0) * light;
}