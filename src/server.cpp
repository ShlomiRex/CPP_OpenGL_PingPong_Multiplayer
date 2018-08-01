#include "server.h"
using namespace std;
using namespace proto;
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


	void* buff = malloc(BUFF_MAX_LEN);


	int players_logged_in = 0;

	while(players_logged_in != 2) {
		receive_packet(sock, buff, BUFF_MAX_LEN, client);
		cout << "> Received from: " << inet_ntoa(client.sin_addr) << endl;


		basic_packet* bp = (basic_packet*)buff;
		if(bp->proto != LOGIN) {
			cerr << "> Packet protocol: " << getProtoName(bp->proto) << " is not login packet" << endl;
		} else {
			login_packet* lp = (login_packet*)buff;
			cout << "Player 1 name: " << lp->name << endl;
		}
	}

}