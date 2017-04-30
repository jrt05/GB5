#pragma once

#include <string>

#include "Graphics.h"
#include "Emulator.h"

class State {
protected:
    State() {};
public:
    virtual ~State() {}
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void redoTexture() = 0;
};

class PauseState : public State {
public:
    PauseState(GFXs *g);
    ~PauseState();
    void draw();
    void update();
    void redoTexture();
private:
    GFXs *graphics;
    SDL_Texture *texture;
    Uint32 *pixels;
};

class MenuState : public State {
public:
    MenuState(GFXs *g);
    ~MenuState();
    void draw();
    void update();
    void redoTexture();
private:
    GFXs *graphics;
    SDL_Texture *texture;
    BMP fpix;
};

class GameState : public State {
public:
    GameState(GFXs *g);
    ~GameState();
    void draw();
    void update();
    void redoTexture();
    bool loadRom(std::wstring f);
    bool isRunning() { return running; }
private:
    Emulator *emulator;
    void destroy_emulator();
    GFXs *graphics;
    SDL_Texture *texture;
    Uint32 * pixels;
    bool paused;
    bool running;
};