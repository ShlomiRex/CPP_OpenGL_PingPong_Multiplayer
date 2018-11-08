#include "network.h"
//target = Who to send the packet
size_t send_packet(int sock, const void* buf, const size_t size, struct sockaddr_in &target) {
    return sendto(sock, buf, size, SEND_FLAGS, (struct sockaddr*)&target, sizeof(target));
}
//source = Who send me the packet
size_t receive_packet(int sock, void* buf, const size_t size, struct sockaddr_in &source) {
    socklen_t source_size = sizeof(source);
    return recvfrom(sock, buf, size, RECEIVE_FLAGS, (struct sockaddr*)&source, &source_size); //Receive the client.
}

namespace proto {
    const char* getProtoName(const proto_t& p) {
        switch(p) {
            case LOGIN:
                return "LOGIN";
            case LOGIN_CONFIRM:
                return "LOGIN_CONFIRM";
            case LOGIN_NOT_CONFIRM:
                return "LOGIN_NOT_CONFIRM";
            case GAME_STARTS:
                return "GAME_STARTS";
            case FIN:
                return "FIN";
            case PLAYER_POS:
                return "PLAYER_POS";
            case BALL:
                return "BALL";
            case TEST:
                return "TEST";
            case NO_PROTO:
                return "NO PROTO";
        }
    }
};