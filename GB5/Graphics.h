#pragma once
#include "Logger.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_syswm.h>
#include <string>

class BMP {
public:
    BMP() { pixels = NULL; width = 0; height = 0; }
    ~BMP() { if (pixels != NULL) delete pixels; pixels = NULL; }
    Uint32 *pixels;
    int width;
    int height;
};

//namespace Graphics {
class GFXs {
public:
    const unsigned int SCREEN_WIDTH = 160;
    const unsigned int SCREEN_HEIGHT = 144;

    // Grahpics mode
    const unsigned int NEAREST = 0;
    const unsigned int BILINEAR = 1;

    // Scale
    const unsigned int SMALL = 4;
    const unsigned int MEDIUM = 5;
    const unsigned int LARGE = 6;
    GFXs();
    ~GFXs();

    unsigned int getScale() { return SCALE; }
    void setScale(int);

    void changeWindowSize();

    void draw();
    void draw(SDL_Texture *t, int x, int y, int w, int h);
    void draw(SDL_Texture *t);
    void clear();
    void commit();
    void setGraphicsMode(int m);
    bool isGraphicsModeSet(int m);
    bool initialized() { return success; }
    void buildString(std::string, BMP &b);
    SDL_Texture *getTextureFromBMP(char *);
    SDL_Texture *getTexture(int w, int h);
    //SDL_Window *getWindow() { return window; }
    HMENU *getMenu() { return &mMenu; }

private:
    unsigned int SCALE = 4;
    int currentGraphicsMode;
    void readBMP(const char *, BMP &b);
    void destroy();
    void create();
    SDL_Window *window;     // Create window
    SDL_Renderer *renderer; // Window renderer
    SDL_GLContext context;

    std::string errorMsg;
    bool success;
    const Uint32 clearNum = 0xFF6496C8;

    SDL_SysWMinfo wmInfo;
    HWND mHandle;
    HMENU mMenu;

    BMP font;
};

