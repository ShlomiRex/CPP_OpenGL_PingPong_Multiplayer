#include "collision.h"

rectangle_collision_borders checkCollision(moving_circle* ball, rectangle* player_body, bool isLeftRect) {
    double x = ball->getCenter().getX();
    double y = ball->getCenter().getY();
    size_t r = ball->getRadius();
    if(isLeftRect) {
        point a = point(player_body->location.getX(), player_body->location.getY());
        point b = point(player_body->location.getX() + player_body->getWidth(), player_body->location.getY());
        point c = point(player_body->location.getX(), player_body->location.getY()+player_body->getHeight());
        point d = point(player_body->location.getX() + player_body->getWidth(), player_body->location.getY()+player_body->getHeight());
        
        //Check if ball is between the height of the player body
        if(y+r > b.getY() && y-r < d.getY()) {
            //Check right border collision
            if(x-r < b.getX()) {
                return rectangle_collision_borders::RIGHT;
            } else if(x+r > a.getX()) {
                return rectangle_collision_borders::LEFT;
            }
        }

        //Check if ball is between the width of the player body
        if(x+r > a.getX() && x-r < b.getX()) {
            //Check collision with top border
            if(y+r > a.getY()) {
                return rectangle_collision_borders::TOP;
            } else if(y-r < c.getY()){
                return rectangle_collision_borders::BOTTOM;
            }
        }

    } else {
        //Right rectangle
        point e = point(player_body->location.getX(), player_body->location.getY());
        point f = point(player_body->location.getX() + player_body->getWidth(), player_body->location.getY()+player_body->getHeight());
        point g = point(player_body->location.getX(), player_body->location.getY()+player_body->getHeight());
        //point h = point(player_body->location.getX() + player_body->getWidth(), player_body->location.getY()+player_body->getHeight());
        
        //Check if ball is between the height of the player body
        if(y+r > e.getY() && y-r < g.getY()) {
            //Check left border collision
            if(x+r > e.getX()) {
                return rectangle_collision_borders::LEFT;
            } else if(x-r < f.getX()) {
                return rectangle_collision_borders::RIGHT;
            }
        }

        // //Check if ball is between the width of the player body
        if(x+r > e.getX() && x-r < f.getX()) {
            //Check collision with top border
            if(y+r > e.getY()) {
                return rectangle_collision_borders::TOP;
            } else if(y-r < g.getY()){
                return rectangle_collision_borders::BOTTOM;
            }
        }
    }

    return rectangle_collision_borders::NONE;
}

//Change ball's behaviour by given collision
//isLeft = is the player that the collision occured is left sided or not
void ballCollided(moving_circle* ball, rectangle_collision_borders border_collided) {
    if(border_collided == NONE)
        return;
    if(border_collided == RIGHT || border_collided == LEFT) {
        ball->setAcceleration( - ball->getAcceleration()->getX(), ball->getAcceleration()->getY());
    } else if(border_collided == TOP || border_collided == BOTTOM) {
        ball->setAcceleration(ball->getAcceleration()->getX(), - ball->getAcceleration()->getY());
    }
}