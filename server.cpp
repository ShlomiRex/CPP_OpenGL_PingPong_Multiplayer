#include "server.h"
using namespace std;


struct sockaddr_in client;
socklen_t client_size = sizeof(client);


void server_start(std::string ip) {
	int sock = socket(AF_INET, SOCK_DGRAM, 0); //Address Family: IPv4. Type: Datagram (UDP). Protocol: 0 (default).
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	bind(sock, (struct sockaddr *) &addr, sizeof(addr)); //Bind to port and ip

    cout << "Waiting for other player to join..." << endl;
    //Receive something from client
	char buf[BUFF_MAX_LEN];
	memset(buf, 0, BUFF_MAX_LEN);
    int flags = 0;
	recvfrom(sock, buf, BUFF_MAX_LEN, flags, (struct sockaddr*)&client, &client_size); //Receive the client.

	cout << "Got: " << buf << endl;
	memset(buf, 0, BUFF_MAX_LEN);
	cout << "Received from: " << inet_ntoa(client.sin_addr) << endl;
	cout << "Sending confirmation..." << endl;
	strcpy(buf, "Hello");
	sendto(sock, buf, BUFF_MAX_LEN, flags, (struct sockaddr*)&client, client_size); //Send confirmation to client.
}