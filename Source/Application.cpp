#include "../../Header/Application.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <array>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Header/Geometry.h"
#include "../Header/Util.h"
#include "../Header/Callbacks.h"
#include "../Header/Rectangle/Rectangle.h"
#include "../Header/Circle/Lamp.h"

// Plan (pseudocode):
// 1. Move the previously-local `ResourceHandles` struct to file scope so it's visible in Init, Run, and Shutdown.
// 2. Keep the same member layout as before so existing code that constructs and uses the struct continues to work.
// 3. In Init(), allocate `ResourceHandles` with `new ResourceHandles{ ... }` and attach it to the GLFW window user pointer.
// 4. In Shutdown(), retrieve the pointer via `glfwGetWindowUserPointer`, cast to `ResourceHandles*`, delete it and null the pointer.
// 5. No other logic changes; resource deletion comments remain for future expansion.

// --- File-scope globals (unchanged) ---
const int NUM_OF_DIGITS = 10 + 1;
const int NUM_OF_SYMBOLS = 3;
// --- Globals used by other modules (kept at file scope so externs keep working) ---
GLFWcursor* remote = nullptr;
GLFWcursor* remoteUpPressed = nullptr;
GLFWcursor* remoteDownPressed = nullptr;
GLFWcursor* remotePowerPressed = nullptr;

bool upPressed = false;
bool downPressed = false;
float xc = -0.53f, yc = 0.59f, r = 0.0045f;
float uLampPower = 0.0f;
bool isFlapMoving = false;
// wanted temp
int currentDigit1Screen1 = 3;
int currentDigit2Screen1 = 5;
// current temp
int currentDigit1Screen2 = 4;
int currentDigit2Screen2 = 1;
int currentSymbol = 0;

// --- ResourceHandles struct moved to file scope so Shutdown can reference it ---
// Only keep resources that are actually created/used.
// texture arrays are stored as std::array to avoid leaks and enable cleanup.
struct ResourceHandles {
    unsigned int bgVAO, bgVBO;
    unsigned int acVAO, acVBO;
    unsigned int flapVAO, flapVBO;
    unsigned int screen1VAO, screen1VBO;
    unsigned int screen2VAO, screen2VBO;
    unsigned int screen3VAO, screen3VBO;
    unsigned int screen1num1VAO, screen1num1VBO;
    unsigned int screen1num2VAO, screen1num2VBO;
    unsigned int screen1degreeVAO, screen1degreeVBO;
    unsigned int screen1celsiusVAO, screen1celsiusVBO;
    unsigned int screen2num1VAO, screen2num1VBO;
    unsigned int screen2num2VAO, screen2num2VBO;
    unsigned int screen2degreeVAO, screen2degreeVBO;
    unsigned int screen2celsiusVAO, screen2celsiusVBO;
    unsigned int lampVAO, lampVBO;
    unsigned int rectShader, circleShader;
    unsigned int bgTexture, acTexture, flapTexture, screenTexture;
    unsigned int lightGreyTexture, darkGreyTexture, degreeTexture, celsiusTexture;
    std::array<unsigned int, NUM_OF_DIGITS> numberTextures;
    std::array<unsigned int, NUM_OF_SYMBOLS> symbolTextures;
};

void check_symbol() {
    int wanted_temp = currentDigit1Screen1 * 10 + currentDigit2Screen1;
    int current_temp = currentDigit1Screen2 * 10 + currentDigit2Screen2;
    if (wanted_temp < current_temp) {
        currentSymbol = 0;
    } else if (wanted_temp > current_temp) {
        currentSymbol = 2;
    } else {
        currentSymbol = 1;
    }
}
void increase_temperature() {
    if (uLampPower == 1.0f) {
        if (currentDigit1Screen1 != 4 || currentDigit2Screen1 != 10) {
            if (currentDigit1Screen1 < 1) {
                currentDigit2Screen1--;
                if (currentDigit2Screen1 == 1) {
                    currentDigit2Screen1 = 1;
                    currentDigit1Screen1 = 1;
                }
            } else {
                currentDigit2Screen1++;
                if (currentDigit2Screen1 == 11) {
                    currentDigit2Screen1 = 1;
                    currentDigit1Screen1++;
                }
            }
        }
    }
}
void lower_temperature() {
    if (uLampPower == 1.0f) {
        if (currentDigit1Screen1 != 0 || currentDigit2Screen1 != 10) {
            if (currentDigit1Screen1 < 1) {
                currentDigit2Screen1++;
                if (currentDigit2Screen1 == 11) {
                    currentDigit2Screen1 = 10;
                    currentDigit1Screen1 = 0;
                }
            } else {
                currentDigit2Screen1--;
                if (currentDigit2Screen1 == 0) {
                    currentDigit1Screen1--;
                    if (currentDigit1Screen1 > 0)
                        currentDigit2Screen1 = 10;
                    else
                        currentDigit2Screen1 = 2;
                }
            }
        }
    }
}

// --- Application implementation ---

Application::Application()
    : window_(nullptr)
{
}

Application::~Application()
{
    // Ensure cleanup if user forgot to call Shutdown
    if (window_ != nullptr) {
        Shutdown();
    }
}

static bool checkTextureLoaded(unsigned int tex, const char* path) {
    if (tex == 0) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return false;
    }
    return true;
}

bool Application::Init()
{
    if (!glfwInit()) {
        std::cerr << "glfwInit failed" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    window_ = glfwCreateWindow(mode->width, mode->height, "AirConditioner", monitor, NULL);
    if (window_ == NULL) {
        std::cerr << "Failed to create the window." << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window_);
    glfwSetMouseButtonCallback(window_, center_callback);

    remote = loadImageToCursor("Resources/remote.png");
    remoteDownPressed = loadImageToCursor("Resources/remote_down_pressed.png");
    remoteUpPressed = loadImageToCursor("Resources/remote_up_pressed.png");
    remotePowerPressed = loadImageToCursor("Resources/remote_power_pressed.png");

    glfwSetCursor(window_, remote);

    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW failed to initialize." << std::endl;
        return false;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // -- Prepare geometry, VAOs, VBOs, textures and shaders --
    unsigned int bgVAO, bgVBO;
    unsigned int acVAO, acVBO;
    unsigned int flapVAO, flapVBO;
    unsigned int screen1VAO, screen1VBO;
    unsigned int screen2VAO, screen2VBO;
    unsigned int screen3VAO, screen3VBO;
    unsigned int screen1num1VAO, screen1num1VBO;
    unsigned int screen1num2VAO, screen1num2VBO;
    unsigned int screen1degreeVAO, screen1degreeVBO;
    unsigned int screen1celsiusVAO, screen1celsiusVBO;
    unsigned int screen2num1VAO, screen2num1VBO;
    unsigned int screen2num2VAO, screen2num2VBO;
    unsigned int screen2degreeVAO, screen2degreeVBO;
    unsigned int screen2celsiusVAO, screen2celsiusVBO;
    unsigned int lampVAO, lampVBO;

    initLampVertices(xc, yc, r);

    initRectangles(mode->width, mode->height, bgVertices, sizeof(bgVertices), bgVAO, bgVBO);
    initRectangles(mode->width, mode->height, acVertices, sizeof(acVertices), acVAO, acVBO);
    initRectangles(mode->width, mode->height, flapVertices, sizeof(flapVertices), flapVAO, flapVBO);
    initRectangles(mode->width, mode->height, screen1Vertices, sizeof(screen1Vertices), screen1VAO, screen1VBO);
    initRectangles(mode->width, mode->height, screen1num1Vertices, sizeof(screen1num1Vertices), screen1num1VAO, screen1num1VBO);
    initRectangles(mode->width, mode->height, screen1num2Vertices, sizeof(screen1num2Vertices), screen1num2VAO, screen1num2VBO);
    initRectangles(mode->width, mode->height, screen1degreeVertices, sizeof(screen1degreeVertices), screen1degreeVAO, screen1degreeVBO);
    initRectangles(mode->width, mode->height, screen1celsiusVertices, sizeof(screen1celsiusVertices), screen1celsiusVAO, screen1celsiusVBO);
    initRectangles(mode->width, mode->height, screen2Vertices, sizeof(screen2Vertices), screen2VAO, screen2VBO);
    initRectangles(mode->width, mode->height, screen2num1Vertices, sizeof(screen2num1Vertices), screen2num1VAO, screen2num1VBO);
    initRectangles(mode->width, mode->height, screen2num2Vertices, sizeof(screen2num2Vertices), screen2num2VAO, screen2num2VBO);
    initRectangles(mode->width, mode->height, screen2degreeVertices, sizeof(screen2degreeVertices), screen2degreeVAO, screen2degreeVBO);
    initRectangles(mode->width, mode->height, screen2celsiusVertices, sizeof(screen2celsiusVertices), screen2celsiusVAO, screen2celsiusVBO);
    initRectangles(mode->width, mode->height, screen3Vertices, sizeof(screen3Vertices), screen3VAO, screen3VBO);

    initCircle(lampVertices, sizeof(lampVertices), lampVAO, lampVBO);

    // load textures and verify each loaded correctly
    unsigned int bgTexture = loadTexture("Resources/background.png");
    if (!checkTextureLoaded(bgTexture, "Resources/background.png")) return false;
    unsigned int acTexture = loadTexture("Resources/air_conditioner.png");
    if (!checkTextureLoaded(acTexture, "Resources/air_conditioner.png")) return false;
    unsigned int flapTexture = loadTexture("Resources/air_vent_grill.png");
    if (!checkTextureLoaded(flapTexture, "Resources/air_vent_grill.png")) return false;
    unsigned int screenTexture = loadTexture("Resources/flap.jpeg");
    if (!checkTextureLoaded(screenTexture, "Resources/flap.jpeg")) return false;
    unsigned int lightGreyTexture = loadTexture("Resources/light_grey.jpg");
    if (!checkTextureLoaded(lightGreyTexture, "Resources/light_grey.jpg")) return false;
    unsigned int darkGreyTexture = loadTexture("Resources/dark_grey.png");
    if (!checkTextureLoaded(darkGreyTexture, "Resources/dark_grey.png")) return false;

    // number and symbol textures - fill arrays
    std::array<unsigned int, NUM_OF_DIGITS> numberTextures{};
    numberTextures[0] = loadTexture("Resources/minus.png"); if (!checkTextureLoaded(numberTextures[0], "Resources/minus.png")) return false;
    numberTextures[1] = loadTexture("Resources/0.png"); if (!checkTextureLoaded(numberTextures[1], "Resources/0.png")) return false;
    numberTextures[2] = loadTexture("Resources/1.png"); if (!checkTextureLoaded(numberTextures[2], "Resources/1.png")) return false;
    numberTextures[3] = loadTexture("Resources/2.png"); if (!checkTextureLoaded(numberTextures[3], "Resources/2.png")) return false;
    numberTextures[4] = loadTexture("Resources/3.png"); if (!checkTextureLoaded(numberTextures[4], "Resources/3.png")) return false;
    numberTextures[5] = loadTexture("Resources/4.png"); if (!checkTextureLoaded(numberTextures[5], "Resources/4.png")) return false;
    numberTextures[6] = loadTexture("Resources/5.png"); if (!checkTextureLoaded(numberTextures[6], "Resources/5.png")) return false;
    numberTextures[7] = loadTexture("Resources/6.png"); if (!checkTextureLoaded(numberTextures[7], "Resources/6.png")) return false;
    numberTextures[8] = loadTexture("Resources/7.png"); if (!checkTextureLoaded(numberTextures[8], "Resources/7.png")) return false;
    numberTextures[9] = loadTexture("Resources/8.png"); if (!checkTextureLoaded(numberTextures[9], "Resources/8.png")) return false;
    numberTextures[10] = loadTexture("Resources/9.png"); if (!checkTextureLoaded(numberTextures[10], "Resources/9.png")) return false;

    std::array<unsigned int, NUM_OF_SYMBOLS> symbolTextures{};
    symbolTextures[0] = loadTexture("Resources/flake.png"); if (!checkTextureLoaded(symbolTextures[0], "Resources/flake.png")) return false;
    symbolTextures[1] = loadTexture("Resources/done.png"); if (!checkTextureLoaded(symbolTextures[1], "Resources/done.png")) return false;
    symbolTextures[2] = loadTexture("Resources/fire.png"); if (!checkTextureLoaded(symbolTextures[2], "Resources/fire.png")) return false;

    unsigned int degreeTexture = loadTexture("Resources/degree.png"); if (!checkTextureLoaded(degreeTexture, "Resources/degree.png")) return false;
    unsigned int celsiusTexture = loadTexture("Resources/celsius.png"); if (!checkTextureLoaded(celsiusTexture, "Resources/celsius.png")) return false;

    // create and validate shaders
    unsigned int rectShader = createShader("Shaders/rect.vert", "Shaders/rect.frag");
    int linkStatus = GL_FALSE;
    glGetProgramiv(rectShader, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        char info[1024]; glGetProgramInfoLog(rectShader, sizeof(info), nullptr, info);
        std::cerr << "rect shader program link error:\n" << info << std::endl;
        return false;
    }

    unsigned int circleShader = createShader("Shaders/circle.vert", "Shaders/circle.frag");
    glGetProgramiv(circleShader, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        char info[1024]; glGetProgramInfoLog(circleShader, sizeof(info), nullptr, info);
        std::cerr << "circle shader program link error:\n" << info << std::endl;
        return false;
    }

    glUseProgram(rectShader);
    glUniform1i(glGetUniformLocation(rectShader, "uTex"), 0);
    glClearColor(0.5f, 0.6f, 1.0f, 1.0f);

        // pack resources and store in window user pointer for Run()/Shutdown()
    ResourceHandles* rh = new ResourceHandles{
        bgVAO, bgVBO,
        acVAO, acVBO,
        flapVAO, flapVBO,
        screen1VAO, screen1VBO,
        screen2VAO, screen2VBO,
        screen3VAO, screen3VBO,
        screen1num1VAO, screen1num1VBO,
        screen1num2VAO, screen1num2VBO,
        screen1degreeVAO, screen1degreeVBO,
        screen1celsiusVAO, screen1celsiusVBO,
        screen2num1VAO, screen2num1VBO,
        screen2num2VAO, screen2num2VBO,
        screen2degreeVAO, screen2degreeVBO,
        screen2celsiusVAO, screen2celsiusVBO,
        lampVAO, lampVBO,
        rectShader, circleShader,
        bgTexture, acTexture, flapTexture, screenTexture,
        lightGreyTexture, darkGreyTexture, degreeTexture, celsiusTexture,
        {}, {} // placeholders for numberTextures and symbolTextures (will assign below)
    };

    // assign arrays
    rh->numberTextures = numberTextures;
    rh->symbolTextures = symbolTextures;

    // store pointer for later cleanup
    glfwSetWindowUserPointer(window_, rh);

    return true;
}

void Application::Run()
{
    ResourceHandles* rh = static_cast<ResourceHandles*>(glfwGetWindowUserPointer(window_));
    if (!rh) return;

    // retrieve handles from resource struct
    unsigned int bgTexture = rh->bgTexture;
    unsigned int acTexture = rh->acTexture;
    unsigned int flapTexture = rh->flapTexture;
    unsigned int screenTexture = rh->screenTexture;
    unsigned int lightGreyTexture = rh->lightGreyTexture;
    unsigned int darkGreyTexture = rh->darkGreyTexture;
    unsigned int degreeTexture = rh->degreeTexture;
    unsigned int celsiusTexture = rh->celsiusTexture;
    auto numberTextures = rh->numberTextures;
    auto symbolTextures = rh->symbolTextures;

    unsigned int rectShader = rh->rectShader;
    unsigned int circleShader = rh->circleShader;

    unsigned int bgVAO = rh->bgVAO;
    unsigned int acVAO = rh->acVAO;
    unsigned int flapVAO = rh->flapVAO;
    unsigned int screen1VAO = rh->screen1VAO;
    unsigned int screen1num1VAO = rh->screen1num1VAO;
    unsigned int screen1num2VAO = rh->screen1num2VAO;
    unsigned int screen1degreeVAO = rh->screen1degreeVAO;
    unsigned int screen1celsiusVAO = rh->screen1celsiusVAO;
    unsigned int screen2VAO = rh->screen2VAO;
    unsigned int screen2num1VAO = rh->screen2num1VAO;
    unsigned int screen2num2VAO = rh->screen2num2VAO;
    unsigned int screen2degreeVAO = rh->screen2degreeVAO;
    unsigned int screen2celsiusVAO = rh->screen2celsiusVAO;
    unsigned int screen3VAO = rh->screen3VAO;
    unsigned int lampVAO = rh->lampVAO;

    while (!glfwWindowShouldClose(window_))
    {
        double initFrameTime = glfwGetTime();

        if (isFlapMoving) {
            if (fill == 0.0f && !uLampPower || fill == 1.0f && uLampPower)
                isFlapMoving = false;
            else
                fill += (uLampPower == 1.0f) ? 0.001f : -0.001f;
        }
        if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            break;
        }
        if (glfwGetKey(window_, GLFW_KEY_UP) == GLFW_PRESS && !upPressed) {
            glfwSetCursor(window_, remoteUpPressed);
            upPressed = true;
            increase_temperature();
        }
        if (glfwGetKey(window_, GLFW_KEY_DOWN) == GLFW_PRESS && !downPressed) {
            glfwSetCursor(window_, remoteDownPressed);
            downPressed = true;
            lower_temperature();
        }

        check_symbol();

        if (glfwGetKey(window_, GLFW_KEY_UP) == GLFW_RELEASE && upPressed) {
            glfwSetCursor(window_, remote);
            upPressed = false;
        }
        if (glfwGetKey(window_, GLFW_KEY_DOWN) == GLFW_RELEASE && downPressed) {
            downPressed = false;
            glfwSetCursor(window_, remote);
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(rectShader);
        useFill = false;
        drawRectangles(rectShader, bgTexture, bgVAO);
        drawRectangles(rectShader, acTexture, acVAO);
        if (uLampPower == 1.0f) {
            drawRectangles(rectShader, lightGreyTexture, screen1VAO);
            drawRectangles(rectShader, lightGreyTexture, screen2VAO);
            drawRectangles(rectShader, numberTextures[currentDigit1Screen1], screen1num1VAO);
            drawRectangles(rectShader, numberTextures[currentDigit2Screen1], screen1num2VAO);
            drawRectangles(rectShader, degreeTexture, screen1degreeVAO);
            drawRectangles(rectShader, celsiusTexture, screen1celsiusVAO);
            drawRectangles(rectShader, numberTextures[currentDigit1Screen2], screen2num1VAO);
            drawRectangles(rectShader, numberTextures[currentDigit2Screen2], screen2num2VAO);
            drawRectangles(rectShader, degreeTexture, screen2degreeVAO);
            drawRectangles(rectShader, celsiusTexture, screen2celsiusVAO);
            drawRectangles(rectShader, symbolTextures[currentSymbol], screen3VAO);
        }
        else {
            drawRectangles(rectShader, darkGreyTexture, screen1VAO);
            drawRectangles(rectShader, darkGreyTexture, screen2VAO);
            drawRectangles(rectShader, darkGreyTexture, screen3VAO);
        }

        useFill = true;
        drawRectangles(rectShader, flapTexture, flapVAO);
        drawCircle(circleShader, lampVAO);
        glfwSwapBuffers(window_);
        glfwPollEvents();
        while (glfwGetTime() - initFrameTime < 1.0 / 75.0) {}
    }
}

void Application::Shutdown()
{
    // retrieve handles and cleanup
    ResourceHandles* rh = static_cast<ResourceHandles*>(glfwGetWindowUserPointer(window_));
    if (rh) {
        // delete VAOs/VBOs
        glDeleteVertexArrays(1, &rh->bgVAO); glDeleteBuffers(1, &rh->bgVBO);
        glDeleteVertexArrays(1, &rh->acVAO); glDeleteBuffers(1, &rh->acVBO);
        glDeleteVertexArrays(1, &rh->flapVAO); glDeleteBuffers(1, &rh->flapVBO);
        glDeleteVertexArrays(1, &rh->screen1VAO); glDeleteBuffers(1, &rh->screen1VBO);
        glDeleteVertexArrays(1, &rh->screen2VAO); glDeleteBuffers(1, &rh->screen2VBO);
        glDeleteVertexArrays(1, &rh->screen3VAO); glDeleteBuffers(1, &rh->screen3VBO);
        glDeleteVertexArrays(1, &rh->screen1num1VAO); glDeleteBuffers(1, &rh->screen1num1VBO);
        glDeleteVertexArrays(1, &rh->screen1num2VAO); glDeleteBuffers(1, &rh->screen1num2VBO);
        glDeleteVertexArrays(1, &rh->screen1degreeVAO); glDeleteBuffers(1, &rh->screen1degreeVBO);
        glDeleteVertexArrays(1, &rh->screen1celsiusVAO); glDeleteBuffers(1, &rh->screen1celsiusVBO);
        glDeleteVertexArrays(1, &rh->screen2num1VAO); glDeleteBuffers(1, &rh->screen2num1VBO);
        glDeleteVertexArrays(1, &rh->screen2num2VAO); glDeleteBuffers(1, &rh->screen2num2VBO);
        glDeleteVertexArrays(1, &rh->screen2degreeVAO); glDeleteBuffers(1, &rh->screen2degreeVBO);
        glDeleteVertexArrays(1, &rh->screen2celsiusVAO); glDeleteBuffers(1, &rh->screen2celsiusVBO);
        glDeleteVertexArrays(1, &rh->lampVAO); glDeleteBuffers(1, &rh->lampVBO);

        // delete textures
        glDeleteTextures(1, &rh->bgTexture);
        glDeleteTextures(1, &rh->acTexture);
        glDeleteTextures(1, &rh->flapTexture);
        glDeleteTextures(1, &rh->screenTexture);
        glDeleteTextures(1, &rh->lightGreyTexture);
        glDeleteTextures(1, &rh->darkGreyTexture);
        glDeleteTextures(1, &rh->degreeTexture);
        glDeleteTextures(1, &rh->celsiusTexture);

        for (auto t : rh->numberTextures) { if (t) glDeleteTextures(1, &t); }
        for (auto t : rh->symbolTextures) { if (t) glDeleteTextures(1, &t); }

        // delete shader programs
        if (rh->rectShader) glDeleteProgram(rh->rectShader);
        if (rh->circleShader) glDeleteProgram(rh->circleShader);

        delete rh;
        glfwSetWindowUserPointer(window_, nullptr);
    }

    // destroy cursors
    if (remote) { glfwDestroyCursor(remote); remote = nullptr; }
    if (remoteUpPressed) { glfwDestroyCursor(remoteUpPressed); remoteUpPressed = nullptr; }
    if (remoteDownPressed) { glfwDestroyCursor(remoteDownPressed); remoteDownPressed = nullptr; }
    if (remotePowerPressed) { glfwDestroyCursor(remotePowerPressed); remotePowerPressed = nullptr; }

    if (window_) {
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }
    glfwTerminate();
}