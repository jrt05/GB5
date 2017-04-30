
#include "InputHandler.h"
#include "Logger.h"
#include "resource.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_events.h>
#include <SDL_syswm.h>

InputHandler::InputHandler() {
    escape = false;
    close_requested = false;
    paused = false;
    load = false;
    bilinear = false;
    small = medium = large = false;
    menu = false;
}

InputHandler::~InputHandler() {

}

bool InputHandler::is_pressed(int key) {
    return (keys[key] && !prevkeys[key]);
}

bool InputHandler::is_held(int key) {
    return keys[key];
}

bool InputHandler::pause_pressed() {
    bool ret = paused;
    paused = false;
    return ret;
}
bool InputHandler::bilinear_pressed() {
    bool ret = bilinear;
    bilinear = false;
    return ret;
}
bool InputHandler::menu_selected() {
    bool ret = menu;
    menu = false;
    return ret;
}
bool InputHandler::small_pressed() {
    bool ret = small;
    small = false;
    return ret;
}
bool InputHandler::medium_pressed() {
    bool ret = medium;
    medium = false;
    return ret;
}
bool InputHandler::large_pressed() {
    bool ret = large;
    large = false;
    return ret;
}
bool InputHandler::load_pressed() {
    bool ret = load;
    load = false;
    return ret;
}

void InputHandler::keydown(SDL_Event &event) {
    keys[event.key.keysym.sym] = true;
}
void InputHandler::keyup(SDL_Event &event) {
    keys[event.key.keysym.sym] = false;
}
void InputHandler::update() {
    prevkeys = keys;

    while (SDL_PollEvent(&windowEvent) != 0) {
        switch (windowEvent.type) {
        case SDL_SYSWMEVENT:
            switch (windowEvent.syswm.msg->msg.win.msg) {
            case WM_COMMAND:
                menu = true;            // Let others know a menu item was selected
                int messageId;
                int wmEvent;
                messageId = LOWORD(windowEvent.syswm.msg->msg.win.wParam);
                wmEvent = HIWORD(windowEvent.syswm.msg->msg.win.wParam);

                switch (messageId) {
                // We want to quit
                case ID_FILE_EXIT:
                    close_requested = true;
                    break;
                case ID_MACHINE_PAUSE:
                    paused = true;
                    break;
                case ID_FILE_LOADGB:
                    load = true;
                    break;
                case ID_SETTINGS_BILINEAR:
                    bilinear = true;
                    break;
                case ID_SIZE_SMALL:
                    small = true;
                    break;
                case ID_SIZE_MEDIUM:
                    medium = true;
                    break;
                case ID_SIZE_LARGE:
                    large = true;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
            break;
        // Check if we want to quit
        case SDL_QUIT:
            close_requested = true;
            break;
        case SDL_KEYDOWN:
            keydown(windowEvent);
            break;
        case SDL_KEYUP:
            keyup(windowEvent);
            break;
        default:
            break;
        }
    }
}