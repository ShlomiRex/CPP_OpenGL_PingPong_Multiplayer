#pragma once

#include "network_limits.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
const int receive_flags = 0;
const int send_flags = 0;
//target = Who to send the packet
void send_packet(int sock, char buf[], struct sockaddr_in target) {
    sendto(sock, buf, BUFF_MAX_LEN, send_flags, (struct sockaddr*)&target, sizeof(target));
}

//source = Who send me the packet
void receive_packet(int sock, char buf[], struct sockaddr_in source) {
    socklen_t source_size = sizeof(source);
    recvfrom(sock, buf, BUFF_MAX_LEN, receive_flags, (struct sockaddr*)&source, &source_size); //Receive the client.
}

void clear_buffer(char buf[]) {
    memset(buf, 0, BUFF_MAX_LEN);
}