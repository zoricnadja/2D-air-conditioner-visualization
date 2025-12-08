#version 330 core

in vec2 chTex;
out vec4 outCol;

uniform sampler2D uTex;
uniform float uFill;
uniform bool uUseFill;
uniform float uWaterLevel;
uniform bool uUseWaterLevel;

void main()
{
    if((chTex.y > uFill && uUseFill) || (chTex.y > uWaterLevel && uUseWaterLevel))
        discard;
    outCol = texture(uTex, chTex);
} 