#include "server.h"
using namespace std;
using namespace proto;
struct sockaddr_in client1, client2;

void server_start(string* ip) {
	//Sock init
	int sock = socket(AF_INET, SOCK_DGRAM, 0); //Address Family: IPv4. Type: Datagram (UDP). Protocol: 0 (default).
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = inet_addr(ip->c_str());
	int bind_result = bind(sock, (struct sockaddr *) &addr, sizeof(addr)); //Bind to port and ip
	if(bind_result != 0) {
		printf("Cannot bind socket: [%d]:[%s]\n", errno, strerror(errno));
		exit(errno);
	}

	cout << "Starting server..." << endl;
	cout << "The Server ip: " << inet_ntoa(addr.sin_addr) << endl;
    cout << "Waiting for other player to join..." << endl;


	void* buff = malloc(BUFF_MAX_LEN);
	unsigned int player_id = 66;
	basic_packet* bp;
	login_packet* lp;
	

try_login1:
	receive_packet(sock, buff, BUFF_MAX_LEN, client1);
	cout << "> Received from: " << inet_ntoa(client1.sin_addr) << endl;

	bp = (basic_packet*)buff;
	if(bp->proto != LOGIN) {
		cerr << "> Packet protocol: " << getProtoName(bp->proto) << " is not login packet" << endl;
		goto try_login1;
	} else {
		lp = (login_packet*)buff;
		cout << "Player 1 name: " << lp->name << endl;
		login_confirm_packet lcp = login_confirm_packet{true, player_id++, DEFAULT_LEFT_STARTING_X, DEFAULT_LEFT_STARTING_Y, DEFAULT_STARTING_WIDTH, DEFAULT_STARTING_HEIGHT}; 
		send_packet(sock, &lcp, sizeof(login_confirm_packet), client1);
	}

try_login2:
	receive_packet(sock, buff, BUFF_MAX_LEN, client2);
	cout << "> Received from: " << inet_ntoa(client2.sin_addr) << endl;

	bp = (basic_packet*)buff;
	if(bp->proto != LOGIN) {
		cerr << "> Packet protocol: " << getProtoName(bp->proto) << " is not login packet" << endl;
		goto try_login2;
	} else {
		lp = (login_packet*)buff;
		cout << "Player 2 name: " << lp->name << endl;
		login_confirm_packet lcp = login_confirm_packet{false, player_id++, DEFAULT_RIGHT_STARTING_X, DEFAULT_RIGHT_STARTING_Y, DEFAULT_STARTING_WIDTH, DEFAULT_STARTING_HEIGHT}; 
		send_packet(sock, &lcp, sizeof(login_confirm_packet), client2);
	}

	game_starts_packet gsp_to_left{
		DEFAULT_RIGHT_STARTING_X,
		DEFAULT_RIGHT_STARTING_Y,
		DEFAULT_STARTING_WIDTH,
		DEFAULT_STARTING_HEIGHT
	};
	
	game_starts_packet gsp_to_right{
		DEFAULT_LEFT_STARTING_X,
		DEFAULT_LEFT_STARTING_Y,
		DEFAULT_STARTING_WIDTH,
		DEFAULT_STARTING_HEIGHT
	};

	send_packet(sock, &gsp_to_left, sizeof(game_starts_packet), client1); //Client 1 is left
	send_packet(sock, &gsp_to_right, sizeof(game_starts_packet), client2); //Client 2 is right

	//!//////////////////////////The game begins!////////////////!////////////////

	struct sockaddr_in client_addr;

	size_t num_of_bytes;
	//TODO: Handle exit of while loop
	while(1) {
		num_of_bytes = receive_packet(sock, buff, BUFF_MAX_LEN, client_addr);
		bp = (basic_packet*)&buff;
		if(client_addr.sin_addr.s_addr == client1.sin_addr.s_addr && client_addr.sin_port == client1.sin_port) {
			//Client 1 send this.

			//TODO: Decedie what to do with packets with proto != player pos
			//if(bp->proto == proto::PLAYER_POS) {
				//Send to client 2 the client 1 position.
				//send_packet(sock, buff, BUFF_MAX_LEN, client2);
			//}

			send_packet(sock, buff, num_of_bytes, client2);
		} else {
			//Client 2 send this.

			//TODO: Decedie what to do with packets with proto != player pos
			//if(bp->proto == proto::PLAYER_POS) {
				//Send to client 1 the client 2 position.
				//send_packet(sock, buff, BUFF_MAX_LEN, client1);
			//}

						
			//Send to client 1 the client 2 position.
			send_packet(sock, buff, num_of_bytes, client1);
		}
	}
	free(buff);
}