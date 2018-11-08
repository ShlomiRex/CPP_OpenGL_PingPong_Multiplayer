#pragma once

//My libs
#include "player.h"
#include "defaults.h"

//STL
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVER_PORT 8888
#define BUFF_MAX_LEN 512 //in bytes
#define SERVER_DEFAULT_IP "127.69.69.69"


#define RECEIVE_FLAGS 0 //Flags for sock recv
#define SEND_FLAGS 0 //Flags for sock send

namespace proto {
    typedef enum proto_t {
        NO_PROTO, LOGIN, LOGIN_CONFIRM, LOGIN_NOT_CONFIRM, GAME_STARTS, FIN, PLAYER_POS, TEST, BALL
    } proto_t;

    //All packets must inherit this struct
    struct basic_packet {
        const proto_t proto;
        basic_packet() : proto(NO_PROTO) {}
        basic_packet(proto_t proto) : proto(proto) {}
        
    };

    //Client send login to server
    struct login_packet : public basic_packet{
        char name[PLAYER_NAME_MAX_LENGTH];
        login_packet(const char n[PLAYER_NAME_MAX_LENGTH]) : basic_packet(LOGIN) {
            strncpy(name, n, PLAYER_NAME_MAX_LENGTH);
        }
    };

    //Server confirms client login and sends him default attributes
    struct login_confirm_packet : public basic_packet {
        bool isLeft;
        unsigned int player_id;

        rectangle starting_rectangle;

        login_confirm_packet(bool isLeft, unsigned int player_id, rectangle starting_rectangle) 
            :  basic_packet(LOGIN_CONFIRM), isLeft(isLeft), player_id(player_id), starting_rectangle(starting_rectangle) {}

        //Contains left player defaults
        static login_confirm_packet getPlayerLeftDefaultPacket(unsigned int player_id) {
            return {
                true, 
                player_id, 
			    rectangle(
				    point(DEFAULT_PLAYER_LEFT_STARTING_X, DEFAULT_PLAYER_LEFT_STARTING_Y),
                    DEFAULT_PLAYER_STARTING_WIDTH,
				    DEFAULT_PLAYER_STARTING_HEIGHT
                )
            };
        }

        //Contains right player defaults
        static login_confirm_packet getPlayerRightDefaultPacket(unsigned int player_id) {
            return {
                false, 
                player_id, 
			    rectangle(
				    point(DEFAULT_PLAYER_RIGHT_STARTING_X, DEFAULT_PLAYER_RIGHT_STARTING_Y),
                    DEFAULT_PLAYER_STARTING_WIDTH,
				    DEFAULT_PLAYER_STARTING_HEIGHT
                )
            };
        }
    };

    struct player_pos_packet : public basic_packet {
        int x, y;
        player_pos_packet(double x, double y) : basic_packet(PLAYER_POS), x(x), y(y) {}
        void update(double new_x, double new_y) {
            x = new_x;
            y = new_y;
        }
    };
    //When 2 players connect to server, the server sends attributes to each player, the data is about the other player.
    //Meanning: Left player recevies right player stats
    //Right player receives left player stats
    struct game_starts_packet : public basic_packet {
        rectangle starting_rectangle;
        moving_circle ball;
        game_starts_packet(rectangle starting_rectangle, moving_circle ball) : basic_packet(GAME_STARTS), starting_rectangle(starting_rectangle), ball(ball) {

        }

        //Contains default right player location
        static game_starts_packet getPlayerRightDefaultPacket() {
            return {
                rectangle(point(DEFAULT_PLAYER_RIGHT_STARTING_X, DEFAULT_PLAYER_RIGHT_STARTING_Y) 
                , DEFAULT_PLAYER_STARTING_WIDTH
		        , DEFAULT_PLAYER_STARTING_HEIGHT)
		        , moving_circle()
	        };
        }

        //Contains default left player location
        static game_starts_packet getPlayerLeftDefaultPacket() {
            return {
                rectangle(point(DEFAULT_PLAYER_LEFT_STARTING_X, DEFAULT_PLAYER_LEFT_STARTING_Y) 
                , DEFAULT_PLAYER_STARTING_WIDTH
		        , DEFAULT_PLAYER_STARTING_HEIGHT)
		        , moving_circle()
	        };
        }
    };

    struct test_packet : public basic_packet{
        char c;
        int i;
        test_packet() : basic_packet(TEST), c('S'), i(666) {}
    };

    struct ball_packet : public basic_packet {
        moving_circle ball;
        ball_packet(moving_circle ball) : basic_packet(proto::BALL) {
            this->ball = ball;
        }
        void update(moving_circle* ball) {
            this->ball = *ball;
        }
    };
    const char* getProtoName(const proto_t& p);
}

//target = Who to send the packet
size_t send_packet(int sock, const void* buf, size_t size, struct sockaddr_in &target);
//source = Who send me the packet
size_t receive_packet(int sock, void* buf, size_t size, struct sockaddr_in &source);

