#pragma once
class point {
protected:
    float x,y;
public:
    point(float x, float y) : x(x),y(y) {
        
    }
    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }
};