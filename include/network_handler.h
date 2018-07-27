#pragma once

#include "utility.h"
#include "player.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include <iostream>
#include <unistd.h>

#define SERVER_PORT 8888
#define BUFF_MAX_LEN 32
#define DEFAULT_IP "127.69.69.69"

const int receive_flags = 0;
const int send_flags = 0;

//target = Who to send the packet
void send_packet(int sock, char* buf, struct sockaddr_in &target);
void clear_buffer(char* buf);
//source = Who send me the packet
void receive_packet(int sock, char* buf, struct sockaddr_in &source);