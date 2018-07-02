#pragma once
#include "network_limits.h"
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

bool start_client(std::string ip);