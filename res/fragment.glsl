#version 330 core
in vec2 _fragUV;

out vec4 _outcolor;

uniform sampler2D u_texture0;

void main()
{
    _outcolor = texture(u_texture0, _fragUV);
}