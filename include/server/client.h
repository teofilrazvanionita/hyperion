#ifndef __CLIENT_H
#define __CLIENT_H

#include "crypto.h"

class CLIENT {
	public:
		CLIENT ();
		~CLIENT ();
		CLIENT (CRYPTO &ci, int &sfd);	// parameters constructor
		bool setCI (CRYPTO &ci);
		bool setSFD (int &sfd);
		CLIENT& operator = (CLIENT &c);	// assignment operator
		CRYPTO& getCI ();
		int& getSFD ();
		CLIENT (CLIENT &c);	// copy constructor
		bool operator == (CLIENT &c);
		bool operator != (CLIENT &c);
	private:
		CRYPTO cryptinfo;
		std::string nume;
		int sockfd;
};

#endif
