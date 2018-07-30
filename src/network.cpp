
#include "network.h"


//target = Who to send the packet
void send_packet(int sock, const void* buf, size_t size, struct sockaddr_in &target) {
    sendto(sock, buf, size, SEND_FLAGS, (struct sockaddr*)&target, sizeof(target));
}

void clear_buffer(char* buf) {
    memset(buf, 0, BUFF_MAX_LEN);
}

//source = Who send me the packet
void receive_packet(int sock, void* buf, size_t size, struct sockaddr_in &source) {
    socklen_t source_size = sizeof(source);
    recvfrom(sock, buf, size, RECEIVE_FLAGS, (struct sockaddr*)&source, &source_size); //Receive the client.
}