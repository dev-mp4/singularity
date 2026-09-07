#version 440 core

in vec2 fUV;
in vec3 fNormal;

uniform sampler2D tex0;

out vec4 fColor;

void main() {
    fColor = mix(texture(tex0, fUV), vec4(fNormal, 1.0), 0.5);
}