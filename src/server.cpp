#include "server.h"
using namespace std;

struct sockaddr_in client;

void server_start(string ip) {
	//Sock init
	int sock = socket(AF_INET, SOCK_DGRAM, 0); //Address Family: IPv4. Type: Datagram (UDP). Protocol: 0 (default).
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	bind(sock, (struct sockaddr *) &addr, sizeof(addr)); //Bind to port and ip

	cout << "Starting server..." << endl;
	cout << "The Server ip: " << inet_ntoa(addr.sin_addr) << endl;
    cout << "Waiting for other player to join..." << endl;

	test_class t;
	receive_packet(sock, &t, sizeof(t), client);

	cout << "Received from: " << inet_ntoa(client.sin_addr) << endl;
	cout << "t.a = " << t.a << endl;
	cout << "Sending confirmation..." << endl;
}


pair<char*, size_t> construct_buffer(int player_pos_x, int player_pos_y, int ball_pos_x, int ball_pos_y) {

}

//Send packets to opponent from the server side
void server_network_loop(bool& running, player& me) {
	while(running) {
		
	}
}