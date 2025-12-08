#pragma once
#include <GLFW/glfw3.h>

extern GLFWcursor* remote;
extern GLFWcursor* remoteUpPressed;
extern GLFWcursor* remoteDownPressed;
extern GLFWcursor* remotePowerPressed;

extern bool upPressed;
extern bool downPressed;
extern bool isFlapMoving;

extern float xc;
extern float yc;
extern float r;

extern float uLampPower;

extern int currentDigit1Screen1;
extern int currentDigit2Screen1;
extern int currentDigit1Screen2;
extern int currentDigit2Screen2;
extern int currentSymbol;