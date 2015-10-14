#ifndef __CLIENT_H
#define __CLIENT_H

#include "crypto.h"

class CLIENT {
	public:
		CLIENT ();
		~CLIENT ();
		bool setCryptInfo (CRYPTO &ci);
		bool setSockFd (int &sfd);
		CLIENT& operator = (CLIENT &c);	// assignment operator
		CRYPTO& getCI ();
		int& getSFD ();
		CLIENT (CLIENT &c);	// copy constructor
	private:
		CRYPTO cryptinfo;
		int sockfd;
};

#endif
