#ifndef __SERVER_H
#define __SERVER_H

#include <list>
#include <thread>
#include <mutex>
#include <iostream>

#include "mesaj.h"
#include "crypto.h"
#include "client.h"

#ifdef __cplusplus
extern "C"
{
#endif
    
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
    
#ifdef __cplusplus
}
#endif


#define PORT "5000"  // the port users will be connecting to
#define BACKLOG 100   // how many pending connections queue will hold

class SERVER {
	public:
		SERVER ();
		~SERVER ();
		bool addMessage (MESAJ &m);
		bool addClient (CLIENT &c);
                bool removeClient (CLIENT &c);
		std::string decryptMSG (std::string &msg, CLIENT &sender);
                std::string decryptMSG (std::string &msg, std::string &pk, std::string &nonce);
		std::string encryptMSG (std::string &msg, CLIENT &receiver);
		bool sendMessage (std::string &msg, CLIENT &sender);	// send message string to the client list
		bool sendMsgToClient (std::string &msg, CLIENT &receiver, bool sendendl);	// send message to the client
                bool sendMessageList (CLIENT &receiver);
                bool verifyName (std::string &nume);
                void mtxLock ();    // locks mutex
                void mtxUnlock ();  // unlocks mutex
                void Play ();
                CLIENT exchangeCIandName (int sockfd);
	private:
		CRYPTO cryptinfo;
		int sockfd;
		std::list<MESAJ> listamesaje;
		std::list<CLIENT> listaclienti;
                std::mutex mtx;     // mutex to syncronize the created threads' operations
};

void client_Communication (SERVER *server_p, int sockfd);

#endif
