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
	private:
		std::string pk;
		std::string sk;
		std::string n;
};

#endif
