
#include "StateManager.h"
#include "State.h"
#include "Graphics.h"
#include "Logger.h"
#include "Time.h"
#include "FileManager.h"
#include "resource.h"

#include <Windows.h>
#include <atlbase.h>

StateManager::StateManager(GFXs *g, InputHandler *i) {
    graphics = g;
    input = i;
    state = PAUSE;
    gs = new GameState(graphics);
    ps = new PauseState(graphics);
    states[GAME] = gs;
    states[PAUSE] = ps;

    if (graphics->getScale() == graphics->SMALL) {
        CheckMenuItem(*graphics->getMenu(), ID_SIZE_SMALL, MF_CHECKED);
    }
    else if (graphics->getScale() == graphics->MEDIUM) {
        CheckMenuItem(*graphics->getMenu(), ID_SIZE_MEDIUM, MF_CHECKED);
    }
    else {
        CheckMenuItem(*graphics->getMenu(), ID_SIZE_LARGE, MF_CHECKED);
    }

    EnableMenuItem(*graphics->getMenu(), ID_MACHINE_PAUSE, MF_DISABLED);
    EnableMenuItem(*graphics->getMenu(), ID_MACHINE_QUIT, MF_DISABLED);
    EnableMenuItem(*graphics->getMenu(), ID_MACHINE_RESTART, MF_DISABLED);

    CheckMenuItem(*graphics->getMenu(), ID_SETTINGS_BILINEAR, MF_UNCHECKED);
    graphics->setGraphicsMode(graphics->NEAREST);

    if (Logger::LogOut.isVerbose()) Logger::LogOut.logstream << "StateManger constructor" << std::endl;
}

StateManager::~StateManager() {
    std::map<int, State*>::iterator iter;
    for (iter = states.begin(); iter != states.end(); iter++) {
        delete iter->second;
    }
    states.clear();
    if (Logger::LogOut.isVerbose()) Logger::LogOut.logstream << "StateManger destructor" << std::endl;
}

void StateManager::update() {
    if (input->is_pressed(SDLK_ESCAPE) || input->pause_pressed()) {
        if (state == PAUSE) {
            if (gs->isRunning()) {
                CheckMenuItem(*graphics->getMenu(), ID_MACHINE_PAUSE, MF_UNCHECKED);
                state = GAME;
            }
        }
        else {
            // If game is running do the following line
            // Mark pause menu item as checked
            CheckMenuItem(*graphics->getMenu(), ID_MACHINE_PAUSE, MF_CHECKED);
            state = PAUSE;
        }
    }

    //////////////
    //////////////
    // Want to use a map <bool, int> for menu items to see if they have been selected


    // We selected a menu item
    if (input->menu_selected()) {
        // Change graphics mode
        if (input->bilinear_pressed()) {
            if (graphics->isGraphicsModeSet(graphics->NEAREST)) {
                CheckMenuItem(*graphics->getMenu(), ID_SETTINGS_BILINEAR, MF_CHECKED);
                graphics->setGraphicsMode(graphics->BILINEAR);
            }
            else {
                CheckMenuItem(*graphics->getMenu(), ID_SETTINGS_BILINEAR, MF_UNCHECKED);
                graphics->setGraphicsMode(graphics->NEAREST);
            }
            states[GAME]->redoTexture();
        }
        // Loading a rom
        if (input->load_pressed()) {
            std::wstring filepath = openDialog();
            if (filepath.compare(L"") != 0) {
                loadRom(filepath);
                state = GAME;
            }
        }

        // Changed size
        if (input->small_pressed()) {
            if (graphics->getScale() != graphics->SMALL) {
                graphics->setScale(graphics->SMALL);
                graphics->changeWindowSize();

                states[GAME]->redoTexture();
                states[PAUSE]->redoTexture();

                CheckMenuItem(*graphics->getMenu(), ID_SIZE_SMALL, MF_CHECKED);
                CheckMenuItem(*graphics->getMenu(), ID_SIZE_MEDIUM, MF_UNCHECKED);
                CheckMenuItem(*graphics->getMenu(), ID_SIZE_LARGE, MF_UNCHECKED);
            }
        }
        if (input->medium_pressed()) {
            if (graphics->getScale() != graphics->MEDIUM) {
                graphics->setScale(graphics->MEDIUM);
                graphics->changeWindowSize();

                states[GAME]->redoTexture();
                states[PAUSE]->redoTexture();

                CheckMenuItem(*graphics->getMenu(), ID_SIZE_SMALL, MF_UNCHECKED);
                CheckMenuItem(*graphics->getMenu(), ID_SIZE_MEDIUM, MF_CHECKED);
                CheckMenuItem(*graphics->getMenu(), ID_SIZE_LARGE, MF_UNCHECKED);
            }
        }
        if (input->large_pressed()) {
            if (graphics->getScale() != graphics->LARGE) {
                graphics->setScale(graphics->LARGE);
                graphics->changeWindowSize();

                states[GAME]->redoTexture();
                states[PAUSE]->redoTexture();

                CheckMenuItem(*graphics->getMenu(), ID_SIZE_SMALL, MF_UNCHECKED);
                CheckMenuItem(*graphics->getMenu(), ID_SIZE_MEDIUM, MF_UNCHECKED);
                CheckMenuItem(*graphics->getMenu(), ID_SIZE_LARGE, MF_CHECKED);
            }
        }
    }

    states[state]->update();
}

void StateManager::loadRom(std::wstring filepath) {
    if (gs->loadRom(filepath)) {
        EnableMenuItem(*graphics->getMenu(), ID_MACHINE_PAUSE, MF_ENABLED);
        EnableMenuItem(*graphics->getMenu(), ID_MACHINE_QUIT, MF_ENABLED);
        EnableMenuItem(*graphics->getMenu(), ID_MACHINE_RESTART, MF_ENABLED);
        USES_CONVERSION;
        Logger::LogOut.logstream << Time::getTimeString() << " Opened ROM " << T2CA(filepath.c_str()) << std::endl;
    }
    else {
        USES_CONVERSION;
        Logger::LogOut.logstream << Time::getTimeString() << " Error: failed to load ROM " << T2CA(filepath.c_str()) << std::endl;
    }
}

void StateManager::draw() {
    states[state]->draw();

    return;
}

void read(TCHAR *filename) {
    size_t pos = 0;// PROGRAM_START;             // Programs start at x'200'
    int length = 0;
    for (std::ifstream f(filename, std::ios::binary); f.good();) {
        int c = f.get();
        if (c == EOF) break;            // End of file
        if (pos > 0xfff) break;         // Game is too long. Might want to abend

        ++length;
    }
    return;
}