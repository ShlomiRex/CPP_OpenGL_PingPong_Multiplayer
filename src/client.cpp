#include "client.h"
using namespace std;
using namespace proto;
void start_client(string ip) {
	//Init socket
	int sock = socket(AF_INET, SOCK_DGRAM, 0); //Address Family: IPv4. Type: Datagram (UDP). Protocol: 0 (default).
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = inet_addr(ip.c_str());

	//login_packet lp = create_login_packet("Shlomi");
	basic_packet bp{};
	cout << "Sending to: " << inet_ntoa(server.sin_addr) << endl;
	cout << "Sending to server..." << endl;
	send_packet(sock, &bp, sizeof(bp),server); 
	cout << "Sent." << endl;
}