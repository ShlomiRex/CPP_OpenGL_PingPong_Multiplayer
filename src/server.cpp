#include "server.h"
using namespace std;
using namespace proto;
struct sockaddr_in client1, client2;
moving_circle* ball_ptr;

void server_start(string *ip, moving_circle* ball)
{
	ball_ptr = ball;
	//[Sock init]
	int sock = socket(AF_INET, SOCK_DGRAM, 0); //Address Family: IPv4. Type: Datagram (UDP). Protocol: 0 (default).
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = inet_addr(ip->c_str());
	int bind_result = bind(sock, (struct sockaddr *)&addr, sizeof(addr)); //Bind to port and ip
	if (bind_result != 0)
	{
		printf("Cannot bind socket: [%d]:[%s]\n", errno, strerror(errno));
		exit(errno);
	}
	//[Sock init end]
	cout << "Starting server..." << endl;
	cout << "The Server ip: " << inet_ntoa(addr.sin_addr) << endl;
	cout << "Waiting for other player to join..." << endl;

	void *buff = malloc(BUFF_MAX_LEN);
	unsigned int player_id = 0;
	basic_packet *bp;
	login_packet *lp;

try_login1:
	receive_packet(sock, buff, BUFF_MAX_LEN, client1);
	cout << "> Received from: " << inet_ntoa(client1.sin_addr) << endl;

	bp = (basic_packet *)buff;
	if (bp->proto != LOGIN)
	{
		cerr << "> Packet protocol: " << getProtoName(bp->proto) << " is not login packet" << endl;
		goto try_login1;
	}
	else
	{
		lp = (login_packet *)buff;
		cout << "Player 1 name: " << lp->name << endl;
		login_confirm_packet lcp = login_confirm_packet::getPlayerLeftDefaultPacket(player_id++);
		cout << "> Sending login confirmation..." << endl;
		send_packet(sock, &lcp, sizeof(login_confirm_packet), client1);
	}

try_login2:
	receive_packet(sock, buff, BUFF_MAX_LEN, client2);
	cout << "> Received from: " << inet_ntoa(client2.sin_addr) << endl;

	bp = (basic_packet *)buff;
	if (bp->proto != LOGIN)
	{
		cerr << "> Packet protocol: " << getProtoName(bp->proto) << " is not login packet" << endl;
		goto try_login2;
	}

	lp = (login_packet *)buff;
	cout << "Player 2 name: " << lp->name << endl;

	//Send confirm login2
	login_confirm_packet lcp = login_confirm_packet::getPlayerRightDefaultPacket(player_id++);
	cout << "> Sending login confirmation..." << endl;
	send_packet(sock, &lcp, sizeof(login_confirm_packet), client2);

	//Initialize ball update thread
	thread ball_thread = thread(ball_thread_function, ball_ptr, sock); //THREAD

	//Prepare packets for sending to players before game begins
	game_starts_packet gsp_to_left = game_starts_packet::getPlayerRightDefaultPacket();
	game_starts_packet gsp_to_right = game_starts_packet::getPlayerLeftDefaultPacket();
	//Send them
	send_packet(sock, &gsp_to_left, sizeof(game_starts_packet), client1);  //Client 1 is left
	send_packet(sock, &gsp_to_right, sizeof(game_starts_packet), client2); //Client 2 is right

	//!//////////////////////////The game begins!////////////////!////////////////

	struct sockaddr_in client_addr;

	size_t num_of_bytes;

	while (1)
	{
		num_of_bytes = receive_packet(sock, buff, BUFF_MAX_LEN, client_addr);
		bp = (basic_packet *)&buff;
		if (client_addr.sin_addr.s_addr == client1.sin_addr.s_addr && client_addr.sin_port == client1.sin_port)
		{
			//Client 1 send this.

			//TODO: Decedie what to do with packets with proto != player pos

			//Send to client 2 the client 1 position.
			send_packet(sock, buff, num_of_bytes, client2);
		}
		else
		{
			//Client 2 send this.

			//TODO: Decedie what to do with packets with proto != player pos

			//Send to client 1 the client 2 position.
			send_packet(sock, buff, num_of_bytes, client1);
		}
	}
	free(buff);
}

void ball_tick(moving_circle* ball_ptr) {
	while(1) {
		double x = ball_ptr->getCenter().getX();
		double y = ball_ptr->getCenter().getY();
		//size_t r = ball_ptr->getRadius();
		point* a = ball_ptr->getAcceleration();

		ball_ptr->setCenter(point(x+a->getX(),y+a->getY()));
		usleep(50);
	}
}

void ball_thread_function(moving_circle* ball_ptr, int sock)
{
	thread ball_tick_thread = thread(ball_tick, ball_ptr);
	
	void *buf = malloc(BUFF_MAX_LEN);
	ball_packet bp = ball_packet(*ball_ptr);
	while(1) {
		//Send ball packet to each client
		send_packet(sock, &bp, BUFF_MAX_LEN, client1);
		send_packet(sock, &bp, BUFF_MAX_LEN, client2);

		bp.update(ball_ptr);

		usleep(500);
	}
	free(buf);
}

