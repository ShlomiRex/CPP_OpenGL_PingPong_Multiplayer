#pragma once

#include "defaults.h"

#include <stdlib.h>
#include <iostream>
using namespace std;
#define PRIMITIVE_T

struct point {
    protected:
    double x,y;
    public:
    point(double x = 0, double y = 0) : x(x),y(y) {
        
    }
    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    void updatePos(double new_x, double new_y) {
        x = new_x;
        y = new_y;
    }

    friend ostream& operator<<(ostream& o, point& p) {
        o << "(" << p.x << "," << p.y << ")";
        return o;
    }
};

struct rectangle {
private:
    size_t width;
    size_t height;
public:
    point location;

    rectangle() : width(0), height(0) {}
    rectangle(point location, size_t width, size_t height) : width(width),height(height),location(location) {

    }

    void updatePos(double new_x, double new_y) {
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


    friend ostream& operator<<(ostream& o, rectangle& rec) {
        o << "( " << rec.location << " , " << rec.width << " . " << rec.height << " )";
        return o;
    }
};

struct moving_circle {
private:
    point acc;
    point center_pos; //Center pos
    size_t radius;

public:
    moving_circle() {
        center_pos = point(DEFAULT_BALL_STARTING_POS_X, DEFAULT_BALL_STARTING_POS_Y);
        acc = point(DEFAULT_BALL_ACC_DX, DEFAULT_BALL_ACC_DY);
        radius = DEFAULT_BALL_RADIUS;
    }

    void update(moving_circle* other) {
        this->center_pos = other->center_pos;
        this->acc = other->acc;
        this->radius = other->radius;
    }

    point getCenter() {
        return center_pos;
    }

    size_t getRadius() {
        return radius;
    }

    point* getAcceleration() {
        return &acc;
    }

    void setAcceleration(double dx, double dy) {
        acc.updatePos(dx, dy);
    }

    void setCenter(point center) {
        this->center_pos = center;
    }

    void setRadius(size_t rad) {
        this->radius = rad;
    }

    friend ostream& operator<<(ostream& o, moving_circle& mc) {
        o << "(acc: " << mc.acc << ",center_pos: " << mc.center_pos << ",radius: " << mc.radius << ")";
        return o;
    }
};

