#include "network.h"
//target = Who to send the packet
void send_packet(int sock, const void* buf, const size_t size, struct sockaddr_in &target) {
    sendto(sock, buf, size, SEND_FLAGS, (struct sockaddr*)&target, sizeof(target));
}
//source = Who send me the packet
void receive_packet(int sock, void* buf, const size_t size, struct sockaddr_in &source) {
    socklen_t source_size = sizeof(source);
    recvfrom(sock, buf, size, RECEIVE_FLAGS, (struct sockaddr*)&source, &source_size); //Receive the client.
}

namespace proto {
    const char* getProtoName(const proto_t& p) {
        switch(p) {
            case LOGIN:
                return "LOGIN";
            case FIN:
                return "FIN";
            case PLAYER_POS:
                return "PLAYER_POS";
            case TEST:
                return "TEST";
            case NO_PROTO:
                return "NO PROTO";
        }
    }
};