#pragma once
#include "Timer.h"
#include "headers.h"
#include "qbRayTrace/qbImage.hpp"
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
    qbImage m_image;
    // SDL2 stuff.
    bool isRunning;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
};
