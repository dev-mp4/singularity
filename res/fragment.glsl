#version 330 core

in vec2 _fraguv;

out vec4 _outcolor;

uniform sampler2D _texture0;

void main()
{
    _outcolor = texture(_texture0, _fraguv);
}