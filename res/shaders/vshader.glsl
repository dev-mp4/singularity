#version 440 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vUV;
layout (location = 2) in vec3 vNormal;

uniform mat4 vModel;
uniform mat4 vProjView;

out vec2 fUV;
out vec3 fNormal;
out vec3 fFragPos;

void main() {
    fUV = vUV;
    fNormal = normalize(mat3(transpose(inverse(vModel))) * vNormal);
    fFragPos = vec3(vModel * vec4(vPos, 1.0f));
    gl_Position = vProjView * vModel * vec4(vPos, 1.0);
}