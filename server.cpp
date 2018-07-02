#include "server.h"
using namespace std;


void server_start(std::string ip) {
	struct sockaddr_in client;
	int sock = socket(AF_INET, SOCK_DGRAM, 0); //Address Family: IPv4. Type: Datagram (UDP). Protocol: 0 (default).
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	bind(sock, (struct sockaddr *) &addr, sizeof(addr)); //Bind to port and ip
	cout << "The Server ip: " << inet_ntoa(addr.sin_addr) << endl;
    cout << "Waiting for other player to join..." << endl;
    //Receive something from client
	char buf[BUFF_MAX_LEN];
	//receive_packet(sock, buf, client);//Receive the client.
	socklen_t client_size = sizeof(client);
    recvfrom(sock, buf, BUFF_MAX_LEN, receive_flags, (struct sockaddr*)&client, &client_size); //Mustn't be in a function cuz function is not changing the client's address
	cout << "Got: " << buf << endl;
	cout << "Received from: " << inet_ntoa(client.sin_addr) << endl;
	cout << "Sending confirmation..." << endl;

	
	usleep(5000000);

	strcpy(buf, "Hello");
	for(int i = 0; i < 100; i++) {
		send_packet(sock, buf, client);
	}
	cout << "Sent." << endl;
	//sendto(sock, buf, BUFF_MAX_LEN, 0, (struct sockaddr*)&client, sizeof(client)); //Send confirmation to client.
}