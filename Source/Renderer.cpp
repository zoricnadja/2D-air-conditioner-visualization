#include "../Header/Renderer.h"
#include "../Header/Rectangle/Rectangle.h"
#include "../Header/Circle/Lamp.h"
#include "../Header/Globals.h"

#include <GL/glew.h>

void Renderer::SetResources(ResourceManager* rm) {
    rm_ = rm;
}

void Renderer::RenderFrame(GLFWwindow* /*window*/) {
    if (!rm_) return;
    auto& R = rm_->Get();

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(R.rectShader);

    // draw background + AC
    useFill = false;
	useWaterLevel = false;
    drawRectangles(R.rectShader, R.bgTexture, R.bgVAO);
    drawRectangles(R.rectShader, R.acTexture, R.acVAO);

    if (uLampPower == 1.0f) {
        drawRectangles(R.rectShader, R.lightGreyTexture, R.screen1VAO);
        drawRectangles(R.rectShader, R.lightGreyTexture, R.screen2VAO);
        drawRectangles(R.rectShader, R.numberTextures[currentDigit1Screen1], R.screen1num1VAO);
        drawRectangles(R.rectShader, R.numberTextures[currentDigit2Screen1], R.screen1num2VAO);
        drawRectangles(R.rectShader, R.degreeTexture, R.screen1degreeVAO);
        drawRectangles(R.rectShader, R.celsiusTexture, R.screen1celsiusVAO);
        drawRectangles(R.rectShader, R.numberTextures[currentDigit1Screen2], R.screen2num1VAO);
        drawRectangles(R.rectShader, R.numberTextures[currentDigit2Screen2], R.screen2num2VAO);
        drawRectangles(R.rectShader, R.degreeTexture, R.screen2degreeVAO);
        drawRectangles(R.rectShader, R.celsiusTexture, R.screen2celsiusVAO);
        drawRectangles(R.rectShader, R.symbolTextures[currentSymbol], R.screen3VAO);
    } else {
        drawRectangles(R.rectShader, R.darkGreyTexture, R.screen1VAO);
        drawRectangles(R.rectShader, R.darkGreyTexture, R.screen2VAO);
        drawRectangles(R.rectShader, R.darkGreyTexture, R.screen3VAO);
    }

    drawRectangleOutline(R.rectShader, R.darkGreyTexture ? R.darkGreyTexture : R.bgTexture, R.waterVAO);

    useFill = true;
    drawRectangles(R.rectShader, R.flapTexture, R.flapVAO);
	useFill = false;
	useWaterLevel = true;
    drawRectangles(R.rectShader, R.waterTexture, R.waterVAO);

    // circle
    drawCircle(R.circleShader, R.lampVAO);
}