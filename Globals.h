#pragma once

#include "Game.h"

class Globals
{
public:
    unsigned int globalTime;
    Game game;
};

extern Globals* globals;