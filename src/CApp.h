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
    CApp() = default;

    int OnExecute();
    bool OnInit();
    void OnEvent(const SDL_Event *event);
    void OnLoop() const;
    void OnRender() const;
    void OnExit();

private:
    inline void PrintVector(const std::string &msg, const qbVector<double> &inputVector) const;

private:
    // An instance of qbImage to store the image.
    qbImage m_image;

    // An instance of the scene class.
    qbRT::Scene m_scene;

    // SDL2 stuff.
    bool isRunning = true;
    SDL_Window *pWindow{nullptr};
    SDL_Renderer *pRenderer{nullptr};
};
