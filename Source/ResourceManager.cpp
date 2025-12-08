#include "../Header/ResourceManager.h"
#include "../Header/Geometry.h"
#include "../Header/Util.h"
#include "../Header/Rectangle.h"
#include "../Header/Lamp.h"
#include "../Header/Globals.h"

#include <iostream>

ResourceManager::~ResourceManager() {
    ReleaseAll();
}

static bool checkTextureLoaded(unsigned int tex, const char* path) {
    if (tex == 0) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return false;
    }
    return true;
}

bool ResourceManager::LoadAll(const GLFWvidmode* mode) {
    // geometry setup
    initLampVertices(xc, yc, r);

    initRectangles(mode->width, mode->height, bgVertices, sizeof(bgVertices), resources_.bgVAO, resources_.bgVBO);
    initRectangles(mode->width, mode->height, acVertices, sizeof(acVertices), resources_.acVAO, resources_.acVBO);
    initRectangles(mode->width, mode->height, flapVertices, sizeof(flapVertices), resources_.flapVAO, resources_.flapVBO);
    initRectangles(mode->width, mode->height, screen1Vertices, sizeof(screen1Vertices), resources_.screen1VAO, resources_.screen1VBO);
    initRectangles(mode->width, mode->height, screen1num1Vertices, sizeof(screen1num1Vertices), resources_.screen1num1VAO, resources_.screen1num1VBO);
    initRectangles(mode->width, mode->height, screen1num2Vertices, sizeof(screen1num2Vertices), resources_.screen1num2VAO, resources_.screen1num2VBO);
    initRectangles(mode->width, mode->height, screen1degreeVertices, sizeof(screen1degreeVertices), resources_.screen1degreeVAO, resources_.screen1degreeVBO);
    initRectangles(mode->width, mode->height, screen1celsiusVertices, sizeof(screen1celsiusVertices), resources_.screen1celsiusVAO, resources_.screen1celsiusVBO);
    initRectangles(mode->width, mode->height, screen2Vertices, sizeof(screen2Vertices), resources_.screen2VAO, resources_.screen2VBO);
    initRectangles(mode->width, mode->height, screen2num1Vertices, sizeof(screen2num1Vertices), resources_.screen2num1VAO, resources_.screen2num1VBO);
    initRectangles(mode->width, mode->height, screen2num2Vertices, sizeof(screen2num2Vertices), resources_.screen2num2VAO, resources_.screen2num2VBO);
    initRectangles(mode->width, mode->height, screen2degreeVertices, sizeof(screen2degreeVertices), resources_.screen2degreeVAO, resources_.screen2degreeVBO);
    initRectangles(mode->width, mode->height, screen2celsiusVertices, sizeof(screen2celsiusVertices), resources_.screen2celsiusVAO, resources_.screen2celsiusVBO);
    initRectangles(mode->width, mode->height, screen3Vertices, sizeof(screen3Vertices), resources_.screen3VAO, resources_.screen3VBO);
    initRectangles(mode->width, mode->height, waterVertices, sizeof(waterVertices), resources_.waterVAO, resources_.waterVBO);

    initCircle(lampVertices, sizeof(lampVertices), resources_.lampVAO, resources_.lampVBO);

    // initialize name overlay rectangle
    initRectangles(mode->width, mode->height, nameVertices, sizeof(nameVertices), resources_.nameVAO, resources_.nameVBO);

    // textures
    resources_.bgTexture = loadTexture("Resources/background.png"); if (!checkTextureLoaded(resources_.bgTexture, "Resources/background.png")) return false;
    resources_.acTexture = loadTexture("Resources/air_conditioner.png"); if (!checkTextureLoaded(resources_.acTexture, "Resources/air_conditioner.png")) return false;
    resources_.flapTexture = loadTexture("Resources/air_vent_grill.png"); if (!checkTextureLoaded(resources_.flapTexture, "Resources/air_vent_grill.png")) return false;
    resources_.screenTexture = loadTexture("Resources/flap.jpeg"); if (!checkTextureLoaded(resources_.screenTexture, "Resources/flap.jpeg")) return false;
    resources_.lightGreyTexture = loadTexture("Resources/light_grey.jpg"); if (!checkTextureLoaded(resources_.lightGreyTexture, "Resources/light_grey.jpg")) return false;
    resources_.darkGreyTexture = loadTexture("Resources/dark_grey.png"); if (!checkTextureLoaded(resources_.darkGreyTexture, "Resources/dark_grey.png")) return false;
    resources_.degreeTexture = loadTexture("Resources/degree.png"); if (!checkTextureLoaded(resources_.degreeTexture, "Resources/degree.png")) return false;
    resources_.celsiusTexture = loadTexture("Resources/celsius.png"); if (!checkTextureLoaded(resources_.celsiusTexture, "Resources/celsius.png")) return false;
    resources_.waterTexture = loadTexture("Resources/water.png"); if (!checkTextureLoaded(resources_.waterTexture, "Resources/water.png")) return false;
	resources_.nameTexture = loadTexture("Resources/name.png"); if (!checkTextureLoaded(resources_.nameTexture, "Resources/name.png")) return false;

    // number textures
    resources_.numberTextures[0] = loadTexture("Resources/minus.png"); if (!checkTextureLoaded(resources_.numberTextures[0], "Resources/minus.png")) return false;
    resources_.numberTextures[1] = loadTexture("Resources/0.png"); if (!checkTextureLoaded(resources_.numberTextures[1], "Resources/0.png")) return false;
    resources_.numberTextures[2] = loadTexture("Resources/1.png"); if (!checkTextureLoaded(resources_.numberTextures[2], "Resources/1.png")) return false;
    resources_.numberTextures[3] = loadTexture("Resources/2.png"); if (!checkTextureLoaded(resources_.numberTextures[3], "Resources/2.png")) return false;
    resources_.numberTextures[4] = loadTexture("Resources/3.png"); if (!checkTextureLoaded(resources_.numberTextures[4], "Resources/3.png")) return false;
    resources_.numberTextures[5] = loadTexture("Resources/4.png"); if (!checkTextureLoaded(resources_.numberTextures[5], "Resources/4.png")) return false;
    resources_.numberTextures[6] = loadTexture("Resources/5.png"); if (!checkTextureLoaded(resources_.numberTextures[6], "Resources/5.png")) return false;
    resources_.numberTextures[7] = loadTexture("Resources/6.png"); if (!checkTextureLoaded(resources_.numberTextures[7], "Resources/6.png")) return false;
    resources_.numberTextures[8] = loadTexture("Resources/7.png"); if (!checkTextureLoaded(resources_.numberTextures[8], "Resources/7.png")) return false;
    resources_.numberTextures[9] = loadTexture("Resources/8.png"); if (!checkTextureLoaded(resources_.numberTextures[9], "Resources/8.png")) return false;
    resources_.numberTextures[10] = loadTexture("Resources/9.png"); if (!checkTextureLoaded(resources_.numberTextures[10], "Resources/9.png")) return false;

    // symbols
    resources_.symbolTextures[0] = loadTexture("Resources/flake.png"); if (!checkTextureLoaded(resources_.symbolTextures[0], "Resources/flake.png")) return false;
    resources_.symbolTextures[1] = loadTexture("Resources/done.png"); if (!checkTextureLoaded(resources_.symbolTextures[1], "Resources/done.png")) return false;
    resources_.symbolTextures[2] = loadTexture("Resources/fire.png"); if (!checkTextureLoaded(resources_.symbolTextures[2], "Resources/fire.png")) return false;

    // shaders
    resources_.rectShader = createShader("Shaders/rect.vert", "Shaders/rect.frag");
    int linkStatus = GL_FALSE;
    glGetProgramiv(resources_.rectShader, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        char info[1024]; glGetProgramInfoLog(resources_.rectShader, sizeof(info), nullptr, info);
        std::cerr << "rect shader link error:\n" << info << std::endl;
        return false;
    }

    resources_.circleShader = createShader("Shaders/circle.vert", "Shaders/circle.frag");
    glGetProgramiv(resources_.circleShader, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        char info[1024]; glGetProgramInfoLog(resources_.circleShader, sizeof(info), nullptr, info);
        std::cerr << "circle shader link error:\n" << info << std::endl;
        return false;
    }

    // set sampler uniform once
    glUseProgram(resources_.rectShader);
    glUniform1i(glGetUniformLocation(resources_.rectShader, "uTex"), 0);

    return true;
}

void ResourceManager::ReleaseAll() {
    // avoid double-delete
    if (resources_.bgVAO) { glDeleteVertexArrays(1, &resources_.bgVAO); glDeleteBuffers(1, &resources_.bgVBO); resources_.bgVAO = 0; }
    if (resources_.acVAO) { glDeleteVertexArrays(1, &resources_.acVAO); glDeleteBuffers(1, &resources_.acVBO); resources_.acVAO = 0; }
    if (resources_.flapVAO) { glDeleteVertexArrays(1, &resources_.flapVAO); glDeleteBuffers(1, &resources_.flapVBO); resources_.flapVAO = 0; }
    if (resources_.screen1VAO) { glDeleteVertexArrays(1, &resources_.screen1VAO); glDeleteBuffers(1, &resources_.screen1VBO); resources_.screen1VAO = 0; }
    if (resources_.screen2VAO) { glDeleteVertexArrays(1, &resources_.screen2VAO); glDeleteBuffers(1, &resources_.screen2VBO); resources_.screen2VAO = 0; }
    if (resources_.screen3VAO) { glDeleteVertexArrays(1, &resources_.screen3VAO); glDeleteBuffers(1, &resources_.screen3VBO); resources_.screen3VAO = 0; }
    if (resources_.lampVAO) { glDeleteVertexArrays(1, &resources_.lampVAO); glDeleteBuffers(1, &resources_.lampVBO); resources_.lampVAO = 0; }
    if (resources_.waterVAO) { glDeleteVertexArrays(1, &resources_.waterVAO); glDeleteBuffers(1, &resources_.waterVBO); resources_.waterVAO = 0; }
    if (resources_.nameVAO) { glDeleteVertexArrays(1, &resources_.nameVAO); glDeleteBuffers(1, &resources_.nameVBO); resources_.nameVAO = 0; }

    if (resources_.bgTexture) { glDeleteTextures(1, &resources_.bgTexture); resources_.bgTexture = 0; }
    if (resources_.acTexture) { glDeleteTextures(1, &resources_.acTexture); resources_.acTexture = 0; }
    if (resources_.flapTexture) { glDeleteTextures(1, &resources_.flapTexture); resources_.flapTexture = 0; }
    if (resources_.screenTexture) { glDeleteTextures(1, &resources_.screenTexture); resources_.screenTexture = 0; }
    if (resources_.lightGreyTexture) { glDeleteTextures(1, &resources_.lightGreyTexture); resources_.lightGreyTexture = 0; }
    if (resources_.darkGreyTexture) { glDeleteTextures(1, &resources_.darkGreyTexture); resources_.darkGreyTexture = 0; }
    if (resources_.degreeTexture) { glDeleteTextures(1, &resources_.degreeTexture); resources_.degreeTexture = 0; }
    if (resources_.celsiusTexture) { glDeleteTextures(1, &resources_.celsiusTexture); resources_.celsiusTexture = 0; }
    if (resources_.waterTexture) { glDeleteTextures(1, &resources_.waterTexture); resources_.waterTexture = 0; }
    if (resources_.nameTexture) { glDeleteTextures(1, &resources_.nameTexture); resources_.nameTexture = 0; }

    for (auto &t : resources_.numberTextures) { if (t) { glDeleteTextures(1, &t); t = 0; } }
    for (auto &t : resources_.symbolTextures) { if (t) { glDeleteTextures(1, &t); t = 0; } }

    if (resources_.rectShader) { glDeleteProgram(resources_.rectShader); resources_.rectShader = 0; }
    if (resources_.circleShader) { glDeleteProgram(resources_.circleShader); resources_.circleShader = 0; }
}