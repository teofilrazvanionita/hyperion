#ifndef __CRYPTO_H
#define __CRYPTO_H

#include "crypto_box.h"


#include <string>
#include <random>
#include <algorithm>
#include <iterator>

class CRYPTO {
	public:
		CRYPTO ();
		~CRYPTO ();
                CRYPTO (std::string &client_pk, std::string &client_nonce);   // incomplete parameters contructor
		CRYPTO & operator = (const CRYPTO &ci);	// assignment operator
		std::string & getPK ();
		std::string & getSK ();
		std::string & getNonce ();
		CRYPTO (const CRYPTO &ci);		// copy constructor
		bool operator == (const CRYPTO &ci);
		bool operator != (const CRYPTO &ci);
	private:
		std::string pk;
		std::string sk;
		std::string n;
};

#endif
