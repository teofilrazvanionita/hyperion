#ifndef __CLIENT_H
#define __CLIENT_H

#include "crypto.h"

class CLIENT {
	public:
		CLIENT ();
		~CLIENT ();
		CLIENT (CRYPTO &ci, int &sfd, std::string &name);	// parameters constructor
		bool setCI (CRYPTO &ci);
		bool setSFD (int &sfd);
		CLIENT& operator = (const CLIENT &c);	// assignment operator
		CRYPTO& getCI ();
		int& getSFD ();
                std::string& getNume ();
		CLIENT (const CLIENT &c);	// copy constructor
		bool operator == (const CLIENT &c);
		bool operator != (const CLIENT &c);
	private:
		CRYPTO cryptinfo;
		std::string nume;
		int sockfd;
};

#endif
