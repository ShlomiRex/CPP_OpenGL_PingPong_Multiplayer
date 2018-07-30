#include "client.h"
using namespace std;

void start_client(string ip) {
	//Init socket
	struct sockaddr_in server;
	int sock = socket(AF_INET, SOCK_DGRAM, 0); //Address Family: IPv4. Type: Datagram (UDP). Protocol: 0 (default).
	struct sockaddr_in endpoint_addr;
	endpoint_addr.sin_family = AF_INET;
	endpoint_addr.sin_port = htons(SERVER_PORT);
	endpoint_addr.sin_addr.s_addr = inet_addr(ip.c_str());

	test_class t;
	t.a = 'E';
	t.b = 69;

	cout << "Sending to: " << inet_ntoa(endpoint_addr.sin_addr) << endl;
	cout << "Sending to server..." << endl;
	send_packet(sock, &t, sizeof(t),endpoint_addr); 
}

pair<char*, size_t> construct_buffer(int player_pos_x, int player_pos_y) {
	size_t buff_size = 8;

	char buff[buff_size];
	char a[4], b[4];
	toByteArray(player_pos_x, a);
	toByteArray(player_pos_y, b);
	char tmp[8];
	strcat(tmp, a);
	strcat(tmp, b);
	for(int i = 0; i < 8; i++) {
		buff[i] = tmp[i];
	}
	return pair<char*, size_t>(buff, 8);
}


//Send packets to server from the opponenet side
void client_network_loop(bool& running, player& me) {
	while(running) {
		construct_buffer(me.getX(), me.getY());
	}
}