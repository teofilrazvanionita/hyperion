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
		std::string decryptMSG (std::string &msg, CLIENT &sender);
		std::string encryptMSG (std::string &msg, CLIENT &receiver);
	private:
		CRYPTO cryptinfo;
		int sockfd;
		std::list<MESAJ> listamesaje;
		std::list<CLIENT> listaclienti;
};

#endif
