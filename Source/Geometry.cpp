#define _USE_MATH_DEFINES
#include <cmath> 
#include "../../Header/Geometry.h"

float bgVertices[] = {
   -1.0f,  1.0f, 0.0f, 1.0f,
   -1.0f, -1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f,
    1.0f,  1.0f, 1.0f, 1.0f
};

float acVertices[] = {
   -1.0f,  1.1f, 0.0f, 1.0f,
   -1.0f,  0.25f, 0.0f, 0.0f,
   -0.45f, 0.25f, 1.0f, 0.0f,
   -0.45f, 1.1f, 1.0f, 1.0f
};

float flapVertices[] = {
   -0.915f, 0.62f, 0.0f, 1.0f,
   -0.91f,  0.585f, 0.0f, 0.0f,
   -0.54f,  0.585f, 1.0f, 0.0f,
   -0.535f, 0.62f, 1.0f, 1.0f
};

float screen1Vertices[] = {
   -0.91f,  0.72f, 0.0f, 1.0f,
   -0.91f,  0.685f, 0.0f, 0.0f,
   -0.85f,  0.685f, 1.0f, 0.0f,
   -0.85f,  0.72f, 1.0f, 1.0f
};

float screen1num1Vertices[] = {
   -0.91f,  0.72f, 0.0f, 1.0f,
   -0.91f,  0.685f, 0.0f, 0.0f,
   -0.895f,  0.685f, 1.0f, 0.0f,
   -0.895f,  0.72f, 1.0f, 1.0f
};

float screen1num2Vertices[] = {
   -0.895f,  0.72f, 0.0f, 1.0f,
   -0.895f,  0.685f, 0.0f, 0.0f,
   -0.88f,  0.685f, 1.0f, 0.0f,
   -0.88f,  0.72f, 1.0f, 1.0f
};

float screen1degreeVertices[] = {
   -0.88f, 0.72f, 0.0f, 1.0f,
   -0.88f, 0.685f, 0.0f, 0.0f,
   -0.865f, 0.685f, 1.0f, 0.0f,
   -0.865f, 0.72f, 1.0f, 1.0f
};

float screen1celsiusVertices[] = {
   -0.865f,  0.72f, 0.0f, 1.0f,
   -0.865f,  0.685f, 0.0f, 0.0f,
   -0.85f,  0.685f, 1.0f, 0.0f,
   -0.85f,  0.72f, 1.0f, 1.0f
};

float screen2Vertices[] = {
   -0.59f,  0.72f, 0.0f, 1.0f,
   -0.59f,  0.685f, 0.0f, 0.0f,
   -0.53f,  0.685f, 1.0f, 0.0f,
   -0.53f,  0.72f, 1.0f, 1.0f
};

float screen2num1Vertices[] = {
   -0.59f,  0.72f, 0.0f, 1.0f,
   -0.59f,  0.685f, 0.0f, 0.0f,
   -0.575f,  0.685f, 1.0f, 0.0f,
   -0.575f,  0.72f, 1.0f, 1.0f
};

float screen2num2Vertices[] = {
   -0.575f,  0.72f, 0.0f, 1.0f,
   -0.575f,  0.685f, 0.0f, 0.0f,
   -0.56f,  0.685f, 1.0f, 0.0f,
   -0.56f,  0.72f, 1.0f, 1.0f
};

float screen2degreeVertices[] = {
   -0.56f, 0.72f, 0.0f, 1.0f,
   -0.56f, 0.685f, 0.0f, 0.0f,
   -0.545f, 0.685f, 1.0f, 0.0f,
   -0.545f, 0.72f, 1.0f, 1.0f
};

float screen2celsiusVertices[] = {
   -0.545f,  0.72f, 0.0f, 1.0f,
   -0.545f,  0.685f, 0.0f, 0.0f,
   -0.53f,  0.685f, 1.0f, 0.0f,
   -0.53f,  0.72f, 1.0f, 1.0f
};

float screen3Vertices[] = {
   -0.621f,  0.72f, 0.0f, 1.0f,
   -0.621f,  0.685f, 0.0f, 0.0f,
   -0.606f,  0.685f, 1.0f, 0.0f,
   -0.606f,  0.72f, 1.0f, 1.0f
};


float lampVertices[NUM_OF_SLICES];
void initLampVertices(float xc, float yc, float r)
{

    lampVertices[0] = xc;
    lampVertices[1] = yc;

    for (int i = 1; i < (NUM_OF_SLICES / 2); ++i) {
        float angle = i * 2.0f * M_PI / (NUM_OF_SLICES / 2 - 2);
        lampVertices[i * 2] = cos(angle) * r + xc;
        lampVertices[i * 2 + 1] = sin(angle) * r + yc;
    }
}


float waterVertices[] = {
   -0.915f, -0.485f, 0.0f, 1.0f,
   -0.91f,  -0.62f, 0.0f, 0.0f,
   -0.54f,  -0.62f, 1.0f, 0.0f,
   -0.535f, -0.485f, 1.0f, 1.0f
};