#pragma once

//My libs
#include "utility.h"
#include "player.h"

//STL
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include <iostream>
#include <unistd.h>

#define SERVER_PORT 8888
#define BUFF_MAX_LEN 32 //in bytes
#define DEFAULT_IP "127.69.69.69"

#define RECEIVE_FLAGS 0 //Flags for sock recv
#define SEND_FLAGS 0 //Flags for sock send

//target = Who to send the packet
void send_packet(int sock, const void* buf, size_t size, struct sockaddr_in &target);
void clear_buffer(char* buf);
//source = Who send me the packet
void receive_packet(int sock, void* buf, size_t size, struct sockaddr_in &source);


class test_class {
public:
    char a;
    int b;
};