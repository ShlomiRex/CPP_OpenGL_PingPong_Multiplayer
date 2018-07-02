#pragma once
#include "network_limits.h"
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>

void start_client(std::string ip);