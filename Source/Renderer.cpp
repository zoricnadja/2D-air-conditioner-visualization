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

    //// --- water basin: increment 'fill' once per second and draw a semi-transparent blue rect ---
    //{
    //    // update fill (you might already do this elsewhere). Example: discrete +1 step per second
    //    // (ensure glfw time is available in your loop)
    //    static double lastFillUpdate = 0.0;
    //    double now = glfwGetTime();
    //    if (lastFillUpdate == 0.0) lastFillUpdate = now;
    //    if (now - lastFillUpdate >= 1.0) {
    //        lastFillUpdate = now;
    //        const float step = 0.05f; // tune speed
    //        fill += step;
    //        if (fill > 1.0f) fill = 1.0f;
    //    }

    //    // debug: print texture + VAO
    //    fprintf(stderr, "waterTexture=%u waterVAO=%u fill=%.3f useFill=%d\n", R.waterTexture, R.waterVAO, fill, (int)useFill);

    //    // draw water basin (enable blending for semi-transparent water)
    //    glEnable(GL_BLEND);
    //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //    useFill = true; // rect.frag will use uFill + uUseFill to clip
    //    useFill = false;
    //    glDisable(GL_BLEND);
    //}

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

    useFill = true;
    drawRectangles(R.rectShader, R.flapTexture, R.flapVAO);
	useFill = false;
	useWaterLevel = true;
    drawRectangles(R.rectShader, R.waterTexture, R.waterVAO);

    // circle
    drawCircle(R.circleShader, R.lampVAO);
}