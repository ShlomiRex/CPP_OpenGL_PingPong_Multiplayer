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

    //Receive login from client 1
	char buf[BUFF_MAX_LEN];
	receive_packet(sock, buf, sizeof(buf), client);

	cout << "Got: " << buf << endl;
	cout << "Received from: " << inet_ntoa(client.sin_addr) << endl;
	cout << "Sending confirmation..." << endl;
	
	usleep(100000); //Wait 0.1 seconds

	strcpy(buf, "Hello");
	send_packet(sock, buf, sizeof(buf),client);
	cout << "Sent." << endl;
}


pair<char*, size_t> construct_buffer(int player_pos_x, int player_pos_y, int ball_pos_x, int ball_pos_y) {

}

//Send packets to opponent from the server side
void server_network_loop(bool& running, player& me) {
	while(running) {
		
	}
}
