#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void ProcessInput(GLFWwindow* window);
void CheckSymbol();
void IncreaseTemperature(int& digit1, int& digit2);
void LowerTemperature(int& digit1, int& digit2);
bool isCold();
bool isHot();