#include "client.h"
using namespace std;

struct sockaddr_in server;
socklen_t server_size = sizeof(server);


void start_client(string ip) {
	int sock = socket(AF_INET, SOCK_DGRAM, 0); //Address Family: IPv4. Type: Datagram (UDP). Protocol: 0 (default).
	struct sockaddr_in endpoint_addr;
	endpoint_addr.sin_family = AF_INET;
	endpoint_addr.sin_port = htons(SERVER_PORT);
	endpoint_addr.sin_addr.s_addr = inet_addr(ip.c_str());

	struct sockaddr* endpoint_sockaddr = (struct sockaddr*)&endpoint_addr;

	char buf[BUFF_MAX_LEN];
	memset(buf, 0, BUFF_MAX_LEN);
	strcpy(buf, "Hi");
    int flags = 0;
	cout << "Sending to server..." << endl;
	sendto(sock, buf, 3, flags, endpoint_sockaddr , sizeof(endpoint_addr)); //Send to server
	
	cout << "Receiving confirmation from server..." << endl;
	memset(buf, 0, BUFF_MAX_LEN);
	recvfrom(sock, buf, BUFF_MAX_LEN, flags, (struct sockaddr*)&server, &server_size); //Receive from server
	cout << "Server sent me: " << buf << endl;
}
