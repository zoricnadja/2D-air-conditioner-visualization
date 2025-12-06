#version 330 core
out vec4 outCol;

uniform float uR;

void main()
{
    outCol = vec4(uR, 0.0, 0.0, 1.0);
} 