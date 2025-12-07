#version 330 core

in vec2 chTex;
out vec4 outCol;

uniform sampler2D uTex;
uniform float uFill;
uniform bool uUseFill;

void main()
{
    if(chTex.y > uFill && uUseFill)
        discard;
    outCol = texture(uTex, chTex);
} 