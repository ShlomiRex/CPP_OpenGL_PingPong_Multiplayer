#include "client.h"
using namespace std;
using namespace proto;

void start_client(string ip, player* me, player* opponent) {
	if(me == nullptr || opponent == nullptr) {
		cerr << "me or opponent is nullptr" << endl;
		exit(1);
	}
	//Init socket
	int sock = socket(AF_INET, SOCK_DGRAM, 0); //Address Family: IPv4. Type: Datagram (UDP). Protocol: 0 (default).
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = inet_addr(ip.c_str());

	string name;
	void* buf = malloc(BUFF_MAX_LEN);
	basic_packet* bp;
	login_confirm_packet* lcp;

enter_name:
	cout << "Please enter your name: " << endl;
	cin >> name;
	if(name.size() >= PLAYER_NAME_MAX_LENGTH) {
		cerr << "ERROR: You must enter a name with length less than " << PLAYER_NAME_MAX_LENGTH << endl;
		goto enter_name;
	}
	me->setName(name.c_str());
	login_packet lp{name.c_str()};
	
	//cout << "Sending to: " << inet_ntoa(server.sin_addr) << endl;
try_login:
	cout << "Trying to login..." << endl;
	send_packet(sock, &lp, sizeof(lp),server); 
	cout << "> Sent." << endl;

	
	receive_packet(sock, buf, BUFF_MAX_LEN, server);
	bp = (basic_packet*)buf;
	if(bp->proto != LOGIN_CONFIRM) {
		cerr << "No confirmation!" << endl;
		goto try_login;
	} else {
		lcp = (login_confirm_packet*)buf;
		cout << "Am I left? Answer: " << lcp->isLeft << endl;
		me->isLeft = lcp->isLeft;
		me->id = lcp->player_id;
		me->height = lcp->starting_height;
		me->width = lcp->starting_width;
		me->pos_x = lcp->starting_pos_x;
		me->pos_y = lcp->starting_pos_y;

		//Opponent isLeft is opposite of me isLeft
		opponent->isLeft = (me->isLeft == true ? false : true);

try_start_game:
		//Now wait for server reply for starting the game...
		receive_packet(sock, buf, BUFF_MAX_LEN, server);
		bp = (basic_packet*)buf;
		if(bp->proto != GAME_STARTS) {
			cerr << "Did not received game starts packet! Trying again." << endl;
			goto try_start_game;
		}
		game_starts_packet* gsp = (game_starts_packet*)buf;
		opponent->width = gsp->starting_width;
		opponent->height = gsp->starting_height;
		opponent->pos_x = gsp->starting_pos_x;
		opponent->pos_y = gsp->starting_pos_y;
		//fisnished initializing clients players. Game starts!
		cout << "Let the games begin!" << endl;

		
	}
}