#ifndef __CLIENT_H
#define __CLIENT_H


#include "crypto.h"
#include "server.h"

class CLIENT {
	public:
            CLIENT ();
            ~CLIENT ();
            void Play ();
            void exchangeCI ();
	private:
            CRYPTO cryptinfo;
            int sockfd;
            SERVER server;
};

#endif
