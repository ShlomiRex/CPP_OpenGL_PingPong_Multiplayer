#pragma once
#include <utility>
#include <string.h>
#include <string>
#include "point.h"
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

struct player {
    char name[PLAYER_NAME_MAX_LENGTH];
    bool isLeft; //Is left board? (on GUI)
    int pos_x, pos_y;
    size_t width, height;
    unsigned int id;

    player() {}
    
    player(char name[PLAYER_NAME_MAX_LENGTH], int x, int y, size_t width, size_t height, bool isLeft, unsigned int id) 
    : isLeft(isLeft),
      pos_x(x),
      pos_y(y),
      width(width),
      height(height),
      id(id) {
        setName(name);
    }

    inline player& operator+=(pair<int,int> p) {
        pos_x += p.first;
        pos_y += p.second;
        return *this;
    }

    inline player& operator-=(pair<int,int> p) {
        pos_x -= p.first;
        pos_y -= p.second;
        return *this;
    }

    inline int getX() const {
        return pos_x;
    }

    inline int getY() const {
        return pos_y;
    }

    inline size_t getWidth() const {
        return width;
    }

    inline size_t getHeight() const {
        return height;
    }

    inline void setName(const char* name) {
        strncpy(this->name, name, PLAYER_NAME_MAX_LENGTH);
    }

    ostream& operator<<(ostream& o) {
        o << "NAME: " << name << " ISLEFT: " << isLeft << " POS_X:" << pos_x << " POS_Y: " << pos_y << endl;
        return o;
    }
};

