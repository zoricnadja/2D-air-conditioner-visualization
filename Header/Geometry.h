#pragma once
constexpr int NUM_OF_SLICES = (50 + 2) * 2;

extern float bgVertices[16];
extern float acVertices[16];
extern float flapVertices[16];

extern float screen1Vertices[16];
extern float screen1num1Vertices[16];
extern float screen1num2Vertices[16];
extern float screen1degreeVertices[16];
extern float screen1celsiusVertices[16];

extern float screen2Vertices[16];
extern float screen2num1Vertices[16];
extern float screen2num2Vertices[16];
extern float screen2degreeVertices[16];
extern float screen2celsiusVertices[16];

extern float screen3Vertices[16];
extern float waterVertices[16];
extern float nameVertices[16];

extern float lampVertices[NUM_OF_SLICES];


void initLampVertices(float xc, float yc, float r);
