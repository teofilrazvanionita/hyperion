#ifndef __SERVER_H
#define __SERVER_H

#include "crypto.h"

class SERVER {
	public:
		SERVER ();
		~SERVER ();
		SERVER (CRYPTO &ci);	// parameters constructor
		bool setCI (CRYPTO &ci);
		SERVER& operator = (const SERVER &s);	// assignment operator
		CRYPTO& getCI ();
		SERVER (const SERVER &s);	// copy constructor
		bool operator == (const SERVER &s);
		bool operator != (const SERVER &s);
	private:
		CRYPTO cryptinfo;
};

#endif
