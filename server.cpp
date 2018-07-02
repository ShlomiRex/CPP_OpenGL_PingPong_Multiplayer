#include "server.h"

bool start() {
	int sock = socket(AF_INET, SOCK_DGRAM, 0); //Address Family: IPv4. Type: Datagram (UDP). Protocol: 0 (default).
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(sock, (struct sockaddr *) &addr, sizeof(addr));
	char buf[50];
	struct sockaddr_in client;
	recvfrom(sock, buf, 50, 0, (struct sockaddr*)&client, sizeof(client));
	printf("Got: %s\n", buf);
    printf("Received from: %s\n", inet_ntoa(client.sin_addr));
    return true;
}