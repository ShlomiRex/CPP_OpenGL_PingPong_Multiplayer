#pragma once

//My libs
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

namespace proto {
    typedef enum proto_t {
        NO_PROTO, LOGIN, FIN, PLAYER_POS, TEST
    } proto_t;

    struct basic_packet {
        const proto_t proto;
        basic_packet() : proto(NO_PROTO) {}
        basic_packet(proto_t proto) : proto(proto) {}
    };

    struct login_packet : public basic_packet{
        const char* name;
        size_t length;
        login_packet(const char* name, size_t length) : basic_packet(LOGIN), name(name), length(length) {}
    };

    struct test_packet : public basic_packet{
        char c;
        int i;
        test_packet() : c('S'), i(20) {}
    };
    const char* getProtoName(const proto_t& p);
}

//target = Who to send the packet
void send_packet(int sock, const void* buf, size_t size, struct sockaddr_in &target);
//source = Who send me the packet
void receive_packet(int sock, void* buf, size_t size, struct sockaddr_in &source);

