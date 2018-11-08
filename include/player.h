#pragma once

#include "geometry.h"
#include "defaults.h"

#include <utility>
#include <string.h>
#include <string>
#include <iostream>
#include <stdbool.h>
using namespace std;

struct player {
    
    char name[PLAYER_NAME_MAX_LENGTH];
    bool isLeft; //Is left board? (on GUI)
    rectangle body;
    unsigned int id;
    
    player() {}
    player(char name[PLAYER_NAME_MAX_LENGTH], int x, int y, size_t width, size_t height, bool isLeft, unsigned int id) 
    : isLeft(isLeft), body(point(x,y),width, height)
    {
        setName(name);
    }
    void setName(const char* name) {
        strncpy(this->name, name, PLAYER_NAME_MAX_LENGTH);
    }

};

