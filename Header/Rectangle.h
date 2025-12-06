#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void initRectangles(int width, int height);
void drawRectangles(unsigned int rectShader);
void deleteRectangles();