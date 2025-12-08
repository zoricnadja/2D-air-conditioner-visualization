#include "../Header/Globals.h"

GLFWcursor* remote = nullptr;
GLFWcursor* remoteUpPressed = nullptr;
GLFWcursor* remoteDownPressed = nullptr;
GLFWcursor* remotePowerPressed = nullptr;

bool upPressed = false;
bool downPressed = false;
bool isFlapMoving = false;
bool isWaterMoving = false;

float xc = -0.53f;
float yc = 0.59f;
float r = 0.0045f;

float uLampPower = 0.0f;

int currentDigit1Screen1 = 3;
int currentDigit2Screen1 = 5;
int currentDigit1Screen2 = 4;
int currentDigit2Screen2 = 1;
int currentSymbol = 0;