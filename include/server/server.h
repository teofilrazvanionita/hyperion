#ifndef __SERVER_H
#define __SERVER_H

#include <list>
#include "mesaj.h"
#include "crypto.h"
#include "client.h"

class SERVER {
	public:
		SERVER ();
		~SERVER ();
		bool addMessage (MESAJ &m);
		bool addClient (CLIENT &c);
	private:
		CRYPTO cryptinfo;
		int sockfd;
		std::list<MESAJ> listamesaje;
		std::list<CLIENT> listaclienti;
};

#endif
