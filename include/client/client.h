#ifndef __CLIENT_H
#define __CLIENT_H


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
	private:
            CRYPTO cryptinfo;
            int sockfd;
            SERVER server;
};

#endif
