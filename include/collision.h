#include "geometry.h"
#pragma once
//For checking collisions
enum rectangle_collision_borders {
    NONE, LEFT, RIGHT, TOP, BOTTOM
};


rectangle_collision_borders checkCollision(moving_circle* ball, rectangle* player_body, bool isLeftRect);