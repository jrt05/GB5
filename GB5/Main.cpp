
#include "Time.h"
#include "Logger.h"
#include "Graphics.h"
#include "InputHandler.h"
#include "StateManager.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_syswm.h>

#include <Windows.h>

#include "resource.h"

int SDL_main(int argc, char *argv[]) {
    Time::start();

    GFXs * graphics = new GFXs();

    if (!graphics->initialized()) {
        Logger::LogOut.logstream << Time::getTimeString() << " Error: Graphics unable to initialize." << std::endl;
        return 1;
    }

    InputHandler *input = new InputHandler();
    StateManager sm(graphics, input);

    bool running = true;
    Time::start();
    long long elapsed = Time::getNanoSeconds();
    while (!input->quit()) {        // Continue until we want to quit
        long long elapsed = Time::getNanoSeconds();
        input->update();            // Update input

        sm.update();

        graphics->clear();
        //graphics->draw();
        sm.draw();
        graphics->commit();
        //graphics->swap();
    }

    delete graphics;
    delete input;
    return 0;
}
