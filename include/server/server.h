#ifndef __SERVER_H
#define __SERVER_H

#include <list>
#include <thread>
#include <mutex>
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
		bool sendMessage (std::string &msg, CLIENT &sender);	// send message string to the client list
		bool sendMsgToClient (std::string &msg, CLIENT &receiver);	// send message to the client
                bool sendMessageList (CLIENT &receiver);
                bool verifyName (std::string &nume);
                void mtxLock ();    // locks mutex
                void mtxUnlock ();  // unlocks mutex
                void Play ();
	private:
		CRYPTO cryptinfo;
		int sockfd;
		std::list<MESAJ> listamesaje;
		std::list<CLIENT> listaclienti;
                std::mutex mtx;     // mutex to syncronize the created threads' operations
};

void client_Communication (SERVER *server_p, int sockfd);

#endif
