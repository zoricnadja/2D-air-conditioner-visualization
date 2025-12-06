#version 330 core
out vec4 outCol;

uniform float uR;

void main()
{
	outCol = vec4(uR, 0.40f, 0.40f, 1.0f);
} 