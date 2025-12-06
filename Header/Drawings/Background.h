#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void initBackground(int width, int height);
void drawBackground(unsigned int rectShader);
void deleteBackground();