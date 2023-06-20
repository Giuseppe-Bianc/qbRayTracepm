#include "CApp.h"

#include "./qbRayTrace/qbLinAlg/qbVector.h"

// The constructor (default)
CApp::CApp() : isRunning(true), pWindow(nullptr), pRenderer(nullptr) {}

bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        QBERROR("SDL could not initialize! SDL_Error: {}", SDL_GetError());
        return false;
    }

    pWindow = SDL_CreateWindow("qbRayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);

    if(pWindow != nullptr) {
        QBINFO("creazione SDL window di dimensioni(w: {}, h: {})", w, h);
        // Initialise the renderer.
        pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(pRenderer == nullptr) {
            QBERROR("SDL could not initialize window! SDL_Error: {}", SDL_GetError());
            SDL_DestroyWindow(pWindow);
            SDL_Quit();
            return false;
        }
        m_image.Initialize(w, h, pRenderer);

        // Set the background color to white.
        SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
        SDL_RenderClear(pRenderer);

        // Render the scene.
        m_scene.Render(m_image);

        // Display the image.
        m_image.Display();

        // Show the result.
        SDL_RenderPresent(pRenderer);

    } else {
        QBERROR("SDL could not initialize window! SDL_Error: {}", SDL_GetError());
        SDL_Quit();
        return false;
    }

    return true;
}

int CApp::OnExecute() {
    SDL_Event event;

    if(OnInit() == false) {
        return -1;
    }

    while(isRunning) {
        while(SDL_PollEvent(&event) != 0) {
            OnEvent(&event);
        }

        OnLoop();
        OnRender();
    }

    OnExit();
    QBSYSPAUSE()
    return 0;
}

void CApp::OnEvent(SDL_Event *event) {
    switch(event->type) {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch(event->key.keysym.sym) {
        case SDLK_ESCAPE:
            isRunning = false;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void CApp::OnLoop() const {}

void CApp::OnRender() const {
    // Set the background color to white.
    // SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    // SDL_RenderClear(pRenderer);

    // Render the scene.
    // m_scene.Render(m_image);

    // Display the image.
    // m_image.Display();

    // Show the result.
    // SDL_RenderPresent(pRenderer);
}

void CApp::OnExit() {
    Timer timer{"OnExit"};
    // Tidy up SDL2 stuff.
    if(pRenderer != nullptr) {
        SDL_DestroyRenderer(pRenderer);
        pRenderer = nullptr;
    }
    if(pWindow != nullptr) {
        SDL_DestroyWindow(pWindow);
        pWindow = nullptr;
    }
    SDL_Quit();
}

// PRIVATE FUNCTIONS.
inline void CApp::PrintVector(const std::string &msg, const qbVector<double> &inputVector) const {
    QBINFO("{} ({}, {}, {})", msg, inputVector.GetElement(0), inputVector.GetElement(1), inputVector.GetElement(2));
}
