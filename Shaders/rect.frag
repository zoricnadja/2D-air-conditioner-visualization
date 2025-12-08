#version 330 core

in vec2 chTex;
out vec4 outCol;

uniform sampler2D uTex;
uniform float uFill;
uniform bool uUseFill;
uniform float uWaterLevel;
uniform bool uUseWaterLevel;
uniform float uAlpha;

void main()
{
    if((chTex.y > uFill && uUseFill) || (chTex.y > uWaterLevel && uUseWaterLevel))
        discard;
    vec4 tex = texture(uTex, chTex);
    tex.a *= uAlpha;
    outCol = tex;
} 
