#pragma once

#include "Graphics.h"

class Emulator {
private:
    GFXs *graphics;
public:
    Emulator(GFXs *g);
    ~Emulator();
    void update() {}
    void draw() {}
};