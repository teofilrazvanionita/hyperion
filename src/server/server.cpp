#include "server.h"

SERVER::SERVER ()
{
        struct addrinfo hints, *servinfo, *p;
        int rv; // return value
        int yes = 1;
        
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE; // use my IP
        
        
        if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
                exit(EXIT_FAILURE);
	}

	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("server: bind");
			continue;
		}
		break;
	}
       
        if (p == NULL)  {
		std::cerr << "server: failed to bind" << std::endl;
		exit (EXIT_FAILURE);
	}

	freeaddrinfo(servinfo); // all done with this structure

	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}
}

SERVER::~SERVER ()
{

}

bool SERVER::addMessage (MESAJ &m)
{
	listamesaje.push_back(m);
	return true;
}

bool SERVER::addClient (CLIENT &c)
{
	listaclienti.push_back(c);
	return true;
}

bool SERVER::removeClient (CLIENT &c)
{
        listaclienti.remove((const CLIENT &)c);
        return true;
}

std::string SERVER::decryptMSG (std::string &msg, CLIENT &sender)
{
	std::string m = crypto_box_open (msg, sender.getCI().getNonce(), sender.getCI().getPK(), cryptinfo.getSK());

	return m;
}

std::string SERVER::decryptMSG (std::string &msg, std::string &pk, std::string &nonce)
{
	std::string m = crypto_box_open (msg, nonce, pk, cryptinfo.getSK());

	return m;
}

std::string SERVER::encryptMSG (std::string &msg, CLIENT &receiver)
{
	std::string c = crypto_box(msg, cryptinfo.getNonce(), receiver.getCI().getPK(), cryptinfo.getSK());

	return c;
}

bool SERVER::sendMessage (std::string &msg, CLIENT &sender)
{
	//std::string m = decryptMSG (msg, sender);

	for(std::list<CLIENT>::iterator it = listaclienti.begin(); it != listaclienti.end(); it++){
		if(*it != sender){
			//std::string c = encryptMSG (m, *it);
                        //std::string cname = encryptMSG (sender.getNume(), *it);
                        //sendMsgToClient (cname, *it, false);
      			//sendMsgToClient (c, *it, true);
                        sendMsgToClient (sender.getNume(), *it, false);
                        sendMsgToClient (msg, *it, false);

		}
	}

	return true;
}

bool SERVER::sendMsgToClient (std::string &msg, CLIENT &receiver, bool sendendl)
{
        if(write(receiver.getSFD(), msg.c_str(), msg.size()) == -1){
                std::cerr << "write() error" << std::endl;
                exit (EXIT_FAILURE);
        }
        if(sendendl){
                if(write(receiver.getSFD(), "\n", 1) == -1){
                        std::cerr << "write() error" << std::endl;
                        exit (EXIT_FAILURE);
                }
        }
	return true;
}

bool SERVER::sendMessageList (CLIENT &receiver)
{
        for(std::list<MESAJ>::iterator it = listamesaje.begin(); it != listamesaje.end(); it++){
               //std::string cname = encryptMSG ((*it).getName(), receiver);
               //std::string enc_comment = encryptMSG ((*it).getComment(), receiver);
               //sendMsgToClient (cname, receiver, false);
               //sendMsgToClient (enc_comment, receiver, true);
               sendMsgToClient ((*it).getName(), receiver, false);
               sendMsgToClient ((*it).getComment(), receiver, false);
        }
        
        return true;
}

bool SERVER::verifyName (std::string &nume)
{
        for(std::list<CLIENT>::iterator it = listaclienti.begin(); it != listaclienti.end(); it++){
                if(!nume.compare((*it).getNume()))
                       return false;
        }
        return true;
}

void SERVER::mtxLock ()
{
        mtx.lock();
}

void SERVER::mtxUnlock ()
{
        mtx.unlock();
}

void SERVER::Play ()
{
        int sfd;
        socklen_t sin_size;
        struct sockaddr their_addr; // connector's address information
        
        while (true){
                sfd = accept(sockfd, &their_addr, &sin_size);
                if(sfd == -1){
                    	perror("accept");
			continue;
                }

                std::thread (client_Communication, this, sfd).detach();
        }
}

void exchangeCI (CLIENT &c)
{
        
}

// do all the communication with the clients in this thread function
void client_Communication (SERVER *server_p, int sockfd)
{
        char buffer[6];
        
        // create fictive client for testing, as we don't have the client program yet... using telnet as client
        CRYPTO client_CI;
        
        std::string numeclient = "client";
        snprintf (buffer, 6, "%d: ", sockfd);
        numeclient += buffer;
        
        CLIENT client(client_CI, sockfd, numeclient);
        
        server_p->mtxLock();
        server_p->addClient(client);
        server_p->sendMessageList(client);
        server_p->mtxUnlock();
        
        write(sockfd, "Welcome to HYPERION Chat Server\n", 32);
        
        while (1){
                char bufread[1024];
                memset (bufread, 0, 1024);
                if(!read(sockfd, bufread, 1024)){
                        server_p->removeClient(client);
                        close (sockfd);
                        return;
                }    // blocks until a message arrives
                
                std::string msg = bufread;
                
                //construct MESAJ object
                MESAJ mes(numeclient, msg);
                
                server_p->mtxLock();
                server_p->addMessage(mes);  // add message to message list
                server_p->sendMessage(msg, client); // send message to the other clients
                server_p->mtxUnlock();        
        }
}