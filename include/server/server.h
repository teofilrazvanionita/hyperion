#ifndef __SERVER_H
#define __SERVER_H

#include <list>
#include "mesaj.h"
#include "crypto.h"

class SERVER {
	public:
		SERVER();
		~SERVER();
	private:
		CRYPTO cryptinfo;
		int sockfd;
		std::list<MESAJ> listamesaje;
};

#endif
