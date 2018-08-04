#pragma once
#include "network.h"
void start_client(std::string ip, player* me, player* opponent);

//Send packets to server from the opponenet side
void client_network_loop(bool& running, player& me);
