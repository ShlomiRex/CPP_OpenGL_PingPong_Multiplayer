#pragma once
#include <utility>
#include <string.h>
#include <string>
#include "geometry.h"
#include "limits.h"
#include <iostream>
#include <stdbool.h>
using namespace std;

//Left player
#define DEFAULT_LEFT_STARTING_X 50
#define DEFAULT_LEFT_STARTING_Y 0

//Right player
#define DEFAULT_RIGHT_STARTING_X 900
#define DEFAULT_RIGHT_STARTING_Y 0

//Both players
#define DEFAULT_STARTING_WIDTH 50
#define DEFAULT_STARTING_HEIGHT 150

//Delta of moving players
#define DeltaY 32

struct player {
    
    char name[PLAYER_NAME_MAX_LENGTH];
    bool isLeft; //Is left board? (on GUI)
    rectangle<int> body;
    unsigned int id;
    player() {}
    player(char name[PLAYER_NAME_MAX_LENGTH], int x, int y, size_t width, size_t height, bool isLeft, unsigned int id) 
    : isLeft(isLeft), body(point<int>(x,y),width, height)
    {
        setName(name);
        acceleration<int> a{10,10};
    }
    void setName(const char* name) {
        strncpy(this->name, name, PLAYER_NAME_MAX_LENGTH);
    }

};

