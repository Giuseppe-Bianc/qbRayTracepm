#pragma once
// clang-format off
#include "Timer.h"
#include "headers.h"
#include "./qbRayTrace/qbImage.hpp"
#include "./qbRayTrace/Scene.hpp"
#include "./qbRayTrace/camera.hpp"
// clang-format on

class CApp {
public:
    CApp();

    int OnExecute();
    bool OnInit();
    void OnEvent(SDL_Event *event);
    void OnLoop() const;
    void OnRender();
    void OnExit();

private:
    inline void PrintVector(const std::string &msg, const qbVector<double> &inputVector) const;

private:
    // An instance of qbImage to store the image.
    qbImage m_image;

    // An instance of the scene class.
    qbRT::Scene m_scene;

    // SDL2 stuff.
    bool isRunning;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
};
