#ifndef __CLIENT_H
#define __CLIENT_H

#include "crypto.h"

class SERVER {
	public:
		SERVER ();
		~SERVER ();
		SERVER (CRYPTO &ci);	// parameters constructor
		bool setCI (CRYPTO &ci);
		SERVER& operator = (const SERVER &c);	// assignment operator
		CRYPTO& getCI ();
		SERVER (const SERVER &c);	// copy constructor
		bool operator == (const SERVER &c);
		bool operator != (SERVER &c);
	private:
		CRYPTO cryptinfo;
};

#endif
