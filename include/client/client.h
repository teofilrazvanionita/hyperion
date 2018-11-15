#ifndef __CLIENT_H
#define __CLIENT_H

#include <thread>

#include "crypto.h"
#include "server.h"

#ifdef __cplusplus
extern "C"
{
#endif
    
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ncurses.h>
    
#ifdef __cplusplus
}
#endif

#define PORT 5000

class CLIENT {
	public:
            CLIENT (char *IP);
            ~CLIENT ();
            void Play ();
            SERVER exchangeCIandName ();
            void sendPK ();
            void sendNonce ();
            std::string recvPK ();
            std::string recvNonce ();
            int getSFD ();
            std::string encryptMSG (std::string &msg, SERVER &receiver);
            std::string decryptMSG (std::string &msg, SERVER &sender);
            SERVER & getServer ();
            WINDOW * getReadWin ();
            WINDOW * getWriteWin ();
	private:
            CRYPTO cryptinfo;
            int sockfd;
            SERVER server;
            bool name_verified;
            WINDOW *read_win;
            WINDOW *write_win;
};


void readLoop (CLIENT *client_p);
void writeLoop (CLIENT *client_p);

#endif
