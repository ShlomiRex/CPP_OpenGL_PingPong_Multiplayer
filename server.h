#pragma once

#include "network_limits.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <string>
#include <iostream>
//Return true if this current client is the left board, return false if the client is the right board
void server_start(std::string ip);