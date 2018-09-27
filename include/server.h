#pragma once
#include <thread>
#include "network.h"
//Return true if this current client is the left board, return false if the client is the right board
void server_start(std::string* ip);
void server_network_loop(bool& running, player& me);
void ball_thread_function();