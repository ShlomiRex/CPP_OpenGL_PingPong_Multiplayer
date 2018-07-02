#include "client.h"
using namespace std;

void start_client(string ip) {
	struct sockaddr_in server;
	int sock = socket(AF_INET, SOCK_DGRAM, 0); //Address Family: IPv4. Type: Datagram (UDP). Protocol: 0 (default).
	struct sockaddr_in endpoint_addr;
	endpoint_addr.sin_family = AF_INET;
	endpoint_addr.sin_port = htons(SERVER_PORT);
	endpoint_addr.sin_addr.s_addr = inet_addr(ip.c_str());

	char buf[BUFF_MAX_LEN];
	strcpy(buf, "Hi");
	cout << "Sending to: " << inet_ntoa(endpoint_addr.sin_addr) << endl;
	cout << "Sending to server..." << endl;
	send_packet(sock, buf, endpoint_addr);
	cout << "Receiving confirmation from server..." << endl;
	receive_packet(sock, buf, server);
	cout << "Server sent me: " << buf << endl;
}
