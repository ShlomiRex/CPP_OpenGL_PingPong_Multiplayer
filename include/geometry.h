#pragma once

#include "defaults.h"

#include <stdlib.h>
#include <iostream>
using namespace std;
#define PRIMITIVE_T

//For checking collisions
enum rectangle_collision_borders {
    NONE, LEFT, RIGHT, TOP, BOTTOM
};

template<typename PRIMITIVE_T T>
struct point {
    protected:
    T x,y;
    public:
    point(T x = 0, T y = 0) : x(x),y(y) {
        
    }
    T getX() const {
        return x;
    }

    T getY() const {
        return y;
    }

    void updatePos(T new_x, T new_y) {
        x = new_x;
        y = new_y;
    }

    ostream& operator<<(ostream& o) {
        o << "(" << x << "," << y << ")";
        return o;
    }
};

template<typename PRIMITIVE_T T>
struct acceleration : protected point<T>{
    public:
    acceleration() {
        
    }
    acceleration(T dx, T dy) {
        setDx(dx);
        setDy(dy);
    }
    T getDx() {
        return this->x;
    }

    T getDy() {
        return this->y;
    }

    void setDx(T dx) {
        this->x = dx;
    }

    void setDy(T dy) {
        this->y = dy;
    }

    void updateAcc(T dx, T dy) {
        setDx(dx);
        setDy(dy);
    }
};




template<typename PRIMITIVE_T T>
struct rectangle {
    private:
    size_t width;
    size_t height;
    public:
    point<T> location;

    rectangle() : width(0), height(0) {}
    rectangle(point<T> location, size_t width, size_t height) : width(width),height(height),location(location) {

    }

    void updatePos(T new_x, T new_y) {
        location.updatePos(new_x, new_y);
    }

    void updateWidth(size_t width){
        this->width = width;
    }

    void updateHeight(size_t height) {
        this->height = height;
    }

    size_t getWidth() { return width; }
    size_t getHeight() { return height; }

    ostream& operator<<(ostream& o) {
        o << "( " << location << " , " << width << " . " << height << " )";
        return o;
    }
};

template<typename PRIMITIVE_T T>
struct moving_circle {
private:
    acceleration<T> acc;
    point<T> center_pos; //Center pos
    size_t radius;

public:
    moving_circle() {
        center_pos = point<T>(DEFAULT_BALL_STARTING_POS_X, DEFAULT_BALL_STARTING_POS_Y);
        acc = acceleration<T>(DEFAULT_BALL_ACC_X, DEFAULT_BALL_ACC_Y);
        radius = DEFAULT_BALL_RADIUS;
    }

    void update(moving_circle* other) {
        this->center_pos = other->center_pos;
        this->acc = other->acc;
        this->radius = other->radius;
    }

    point<T> getCenter() {
        return center_pos;
    }

    size_t getRadius() {
        return radius;
    }
};


rectangle_collision_borders checkCollision(moving_circle<int>* ball, rectangle<int>* rec, bool isLeftRect);