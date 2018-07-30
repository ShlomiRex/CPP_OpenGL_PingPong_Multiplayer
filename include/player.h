#pragma once
#include <string>
#include "point.h"
#include <stdbool.h>
using namespace std;
class player {
protected:
    string name;
    bool isLeft; //Is left board? (on GUI)
    int pos_x, pos_y;
    const size_t width, height;
public:
    player(string name, bool isLeft, int x, int y, size_t width, size_t height) : name(name),isLeft(isLeft),pos_x(x), pos_y(y), width(width), height(height) {
        
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
};

