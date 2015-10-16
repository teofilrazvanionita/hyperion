#include "server.h"

SERVER::SERVER ()
{

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
	std::string m = decryptMSG (msg, sender);

	for(std::list<CLIENT>::iterator it = listaclienti.begin(); it != listaclienti.end(); it++){
		if(*it != sender){
			std::string c = encryptMSG (m, *it);
                        std::string cname = encryptMSG (sender.getNume(), *it);
                        sendMsgToClient (cname, *it, false);
			sendMsgToClient (c, *it, true);
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
               std::string cname = encryptMSG ((*it).getName(), receiver);
               std::string enc_comment = encryptMSG ((*it).getComment(), receiver);
               sendMsgToClient (cname, receiver, false);
               sendMsgToClient (enc_comment, receiver, true);
        }
        
        return true;
}

bool SERVER::verifyName (std::string &nume)
{
        for(std::list<CLIENT>::iterator it = listaclienti.begin(); it != listaclienti.end(); it++){
                if(nume == (*it).getNume())
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
        std::thread (client_Communication, this, 1).detach();
}

// do all the communication with the clients in this thread function
void client_Communication (SERVER *server_p, int sockfd)
{
        server_p->mtxLock();
        server_p->mtxUnlock();
}