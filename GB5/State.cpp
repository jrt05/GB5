

#include "State.h"
#include "Logger.h"

#include "Graphics.h"
#include "Emulator.h"

////////////////////////////////////////////
//
//  MenuState
////////////////////////////////////////////

class MenuItem {
private:
public:
};

MenuState::MenuState(GFXs *g) {
    graphics = g;

    graphics->buildString("File   Edit   View   Settings   Help", fpix);

    texture = graphics->getTexture(fpix.width, fpix.height);
    SDL_UpdateTexture(texture, NULL, fpix.pixels, fpix.width * sizeof(Uint32));  // Copy pixels on to window
    if (Logger::LogOut.isVerbose()) Logger::LogOut.logstream << "MenuState constructor" << std::endl;
}

MenuState::~MenuState() {
    SDL_DestroyTexture(texture);
    if (Logger::LogOut.isVerbose()) Logger::LogOut.logstream << "MenuState destructor" << std::endl;
}
// Recreate the textures with updated graphics renderer
void MenuState::redoTexture() {
    texture = graphics->getTexture(fpix.width, fpix.height);
    SDL_UpdateTexture(texture, NULL, fpix.pixels, fpix.width * sizeof(Uint32));  // Copy pixels on to window
}
void MenuState::update() {

}

void MenuState::draw() {
    //SDL_UpdateTexture(texture, NULL, fpix.pixels, fpix.width * sizeof(Uint32));  // Copy pixels on to window
    graphics->draw(texture, 0, 0, fpix.width, fpix.height);
}

////////////////////////////////////////////
//
//  PauseState
////////////////////////////////////////////

PauseState::PauseState(GFXs *g) {
    graphics = g;

    pixels = new Uint32[graphics->SCREEN_WIDTH * graphics->SCREEN_HEIGHT];

    for (unsigned int x = 0; x != graphics->SCREEN_WIDTH * graphics->SCREEN_HEIGHT; ++x) {
        pixels[x] = 0xFF000098;
        //pixels[x] = 0xFF000063;
    }

    texture = graphics->getTexture(graphics->SCREEN_WIDTH, graphics->SCREEN_HEIGHT);

    SDL_UpdateTexture(texture, NULL, pixels, graphics->SCREEN_WIDTH * sizeof(Uint32));  // Copy pixels on to window

    if (Logger::LogOut.isVerbose()) Logger::LogOut.logstream << "PauseState constructor." << std::endl;
}

PauseState::~PauseState() {
    SDL_DestroyTexture(texture);
    if (Logger::LogOut.isVerbose()) Logger::LogOut.logstream << "PauseState destructor." << std::endl;
}

// Recreate the textures with updated graphics renderer
void PauseState::redoTexture() {
    texture = graphics->getTexture(graphics->SCREEN_WIDTH, graphics->SCREEN_HEIGHT);
    SDL_UpdateTexture(texture, NULL, pixels, graphics->SCREEN_WIDTH * sizeof(Uint32));  // Copy pixels on to window
}

void PauseState::update() {

}

void PauseState::draw() {
    //graphics->draw(texture, 0, 0, graphics->SCREEN_WIDTH * graphics->getScale(), graphics->SCREEN_HEIGHT * graphics->getScale());
    graphics->draw(texture);
}

////////////////////////////////////////////
//
//  GameState
////////////////////////////////////////////
GameState::GameState(GFXs *g) {
    graphics = g;

    pixels = new Uint32[graphics->SCREEN_WIDTH * graphics->SCREEN_HEIGHT];
    memset(pixels, 255, graphics->SCREEN_WIDTH * graphics->SCREEN_HEIGHT * sizeof(Uint32));

    texture = graphics->getTexture(graphics->SCREEN_WIDTH, graphics->SCREEN_HEIGHT);

    emulator = NULL;

    if (Logger::LogOut.isVerbose()) Logger::LogOut.logstream << "GameState constructor" << std::endl;
}

GameState::~GameState() {
    SDL_DestroyTexture(texture);
    destroy_emulator();
    delete pixels;

    if (Logger::LogOut.isVerbose()) Logger::LogOut.logstream << "GameState destructor" << std::endl;
}

void GameState::destroy_emulator() {
    if (emulator != NULL) {
        delete emulator;
        emulator = NULL;
    }
}

// Recreate the textures with updated graphics renderer
void GameState::redoTexture() {
    texture = graphics->getTexture(graphics->SCREEN_WIDTH, graphics->SCREEN_HEIGHT);
    SDL_UpdateTexture(texture, NULL, pixels, graphics->SCREEN_WIDTH * sizeof(Uint32));  // Copy pixels on to window
}

bool GameState::loadRom(std::wstring f) {
    running = true;
    return true;
}

void GameState::draw() {
    int count = 0;
    SDL_UpdateTexture(texture, NULL, pixels, graphics->SCREEN_WIDTH * sizeof(Uint32));  // Copy pixels on to window
    SDL_Rect rect;
    rect.w = graphics->SCREEN_WIDTH * graphics->getScale();
    rect.h = graphics->SCREEN_HEIGHT * graphics->getScale();
    rect.x = 0; rect.y = 0;

    graphics->draw(texture);
}

void GameState::update() {
    for (unsigned int x = 0; x < graphics->SCREEN_WIDTH * graphics->SCREEN_HEIGHT; ++x) {
        if (x % 3 == 0)
            pixels[x] = 0xFF0000FF;
        else if (x % 3 == 1)
            pixels[x] = 0xFF00FF00;
        else
            pixels[x] = 0xFFFF0000;
    }
}