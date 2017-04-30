#pragma once

#include <vector>
#include <string>

#include "Graphics.h"
#include "State.h"
#include "InputHandler.h"

class StateManager {
public:
    StateManager(GFXs *g, InputHandler *i);
    ~StateManager();
    void draw();
    void update();
private:
    void loadRom(std::wstring s);
    GFXs *graphics;
    InputHandler *input;
    GameState *gs;
    PauseState *ps;
    std::map<int, State *> states;
    int state;
    enum {
        MENU,
        PAUSE,
        GAME
    };
};