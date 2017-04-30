#pragma once

#include <map>
#include <vector>

#include <SDL_events.h>

class InputHandler {
private:
    SDL_Event windowEvent;

    bool escape;
    bool close_requested;
    bool paused;
    bool load;
    bool bilinear;
    bool small;
    bool medium;
    bool large;
    bool menu;

    std::map<int, bool> keys;
    std::map<int, bool> prevkeys;
    std::map<int, bool> winEvents;
    std::map<int, bool> prevWinEvents;

    void keydown(SDL_Event &event);
    void keyup(SDL_Event &event);

public:
    InputHandler();
    ~InputHandler();
    void update();
    bool quit() { return close_requested; }
    bool is_held(int key);
    bool is_pressed(int key);
    bool pause_pressed();
    bool load_pressed();
    bool bilinear_pressed();
    bool small_pressed();
    bool medium_pressed();
    bool large_pressed();
    bool menu_selected();
};