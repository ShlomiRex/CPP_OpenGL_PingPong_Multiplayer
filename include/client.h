#pragma once
#include "network.h"
void start_client(std::string ip, player* me, player* opponent, moving_circle* ball);



void sendto_network_loop(bool* running, player* me);
void recvfrom_network_loop(bool* running, player* opponent);
