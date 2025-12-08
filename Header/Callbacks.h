#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
extern GLFWcursor* remote;
extern GLFWcursor* remotePowerPressed;
extern float xc, yc, r;
extern bool isFlapMoving;
extern float uLampPower;
extern float fill;
extern bool useFill;
extern bool useWaterLevel;
extern float waterLevel;


void center_callback(GLFWwindow* window, int button, int action, int mods);