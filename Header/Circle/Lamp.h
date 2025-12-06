#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

extern const int NUM_SLICES;
extern float uLampPower;
void initCircle(float* vertices, size_t size, unsigned int& vao, unsigned int& vbo);
void drawCircle(unsigned int shader, unsigned int& vao);
void deleteCircle(unsigned int& vao, unsigned int& vbo);