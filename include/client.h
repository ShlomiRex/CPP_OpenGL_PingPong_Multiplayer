#pragma once
#include "network_handler.h"
void start_client(std::string ip);

//Send packets to server from the opponenet side
void client_network_loop(bool& running, player& me);
