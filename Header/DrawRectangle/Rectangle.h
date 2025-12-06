#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void initRectangles(int width, int height, float* vertices, size_t size, unsigned int& vao, unsigned int& vbo);
unsigned int loadTexture(const char* path);
void drawRectangles(unsigned int shader, unsigned int texture, unsigned int& vao);
void deleteRectangles(unsigned int& vao, unsigned int& vbo, unsigned int texture);