#pragma once
#include <thread>
#include "network.h"
#include "geometry.h"
//Return true if this current client is the left board, return false if the client is the right board
void server_start(std::string*, moving_circle*);
void server_network_loop(bool& running, player& me);
void ball_thread_function(moving_circle* ball_ptr, int sock);
void ball_tick(moving_circle* ball_ptr);