#include "client.h"
using namespace std;
bool start_client(string ip) {
	int sock = socket(AF_INET, SOCK_DGRAM, 0); //Address Family: IPv4. Type: Datagram (UDP). Protocol: 0 (default).
	struct sockaddr_in endpoint_addr;
	endpoint_addr.sin_family = AF_INET;
	endpoint_addr.sin_port = htons(SERVER_PORT);
	endpoint_addr.sin_addr.s_addr = inet_addr(ip.c_str());

	struct sockaddr* endpoint_sockaddr = (struct sockaddr*)&endpoint_addr;

    string buf = "Hi";
    size_t buf_size = sizeof(buf)/sizeof(char);
    int flags = 0;
	sendto(sock, buf.c_str(), buf_size, flags, endpoint_sockaddr , sizeof(endpoint_addr));

    return false;
}