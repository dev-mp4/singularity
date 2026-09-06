#version 440 core

in vec2 fUV;

uniform sampler2D tex0;

out vec4 fColor;

void main() {
    fColor = texture(tex0, fUV);
}