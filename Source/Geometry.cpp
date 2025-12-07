#include "../Header/Geometry.h"

float bgVertices[16] = {
   -1.0f,  1.0f, 0.0f, 1.0f,
   -1.0f, -1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f,
    1.0f,  1.0f, 1.0f, 1.0f
};

float acVertices[16] = {
   -1.0f,  1.1f, 0.0f, 1.0f,
   -1.0f,  0.25f, 0.0f, 0.0f,
   -0.45f, 0.25f, 1.0f, 0.0f,
   -0.45f, 1.1f, 1.0f, 1.0f
};

float flapVertices[16] = {
   -0.915f, 0.62f, 0.0f, 1.0f,
   -0.91f,  0.585f, 0.0f, 0.0f,
   -0.54f,  0.585f, 1.0f, 0.0f,
   -0.535f, 0.62f, 1.0f, 1.0f
};

// ✅ Screens
float screen1Vertices[16] = {
   -0.91f,  0.72f, 0.0f, 1.0f,
   -0.91f,  0.685f, 0.0f, 0.0f,
   -0.85f,  0.685f, 1.0f, 0.0f,
   -0.85f,  0.72f, 1.0f, 1.0f
};

float screen1num1Vertices[16] = {
   -0.91f,  0.72f, 0.0f, 1.0f,
   -0.91f,  0.685f, 0.0f, 0.0f,
   -0.895f,  0.685f, 1.0f, 0.0f,
   -0.895f,  0.72f, 1.0f, 1.0f
};

float screen1num2Vertices[16] = {
   -0.895f,  0.72f, 0.0f, 1.0f,
   -0.895f,  0.685f, 0.0f, 0.0f,
   -0.88f,   0.685f, 1.0f, 0.0f,
   -0.88f,   0.72f, 1.0f, 1.0f
};

float screen1degreeVertices[16] = {
   -0.88f, 0.72f, 0.0f, 1.0f,
   -0.88f, 0.685f, 0.0f, 0.0f,
   -0.865f,0.685f, 1.0f, 0.0f,
   -0.865f,0.72f, 1.0f, 1.0f
};

float screen1celsiusVertices[16] = {
   -0.865f, 0.72f, 0.0f, 1.0f,
   -0.865f, 0.685f, 0.0f, 0.0f,
   -0.85f,  0.685f, 1.0f, 0.0f,
   -0.85f,  0.72f, 1.0f, 1.0f
};

float* lampVertices = nullptr;

void initLampVertices(int numSlices, float xc, float yc, float r)
{
    delete[] lampVertices;
    lampVertices = new float[(numSlices + 2) * 2];

    lampVertices[0] = xc;
    lampVertices[1] = yc;

    for (int i = 1; i < numSlices + 2; ++i) {
        float angle = i * 2.0f * 3.1415926f / numSlices;
        lampVertices[i * 2] = cos(angle) * r + xc;
        lampVertices[i * 2 + 1] = sin(angle) * r + yc;
    }
}
