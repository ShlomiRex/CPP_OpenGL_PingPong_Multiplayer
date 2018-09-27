#include "geometry.h"

rectangle_collision_borders checkCollision(moving_circle<int>* ball, rectangle<int>* rec, bool isLeftRect) {
    if(isLeftRect) {
        //Check collision with right border
        if(rec->location.getX() > ball->getCenter().getX() + ball->getRadius()) {
            return rectangle_collision_borders::RIGHT;
        }
    } else {

    }
}