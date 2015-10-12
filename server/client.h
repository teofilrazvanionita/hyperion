#ifndef __CLIENT_H
#define __CLIENT_H

#include "crypto.h"

class CLIENT {
	public:
		CLIENT();
		~CLIENT();
	private:
		CRYPTO cryptinfo;
		int sockfd;
}

#endif
