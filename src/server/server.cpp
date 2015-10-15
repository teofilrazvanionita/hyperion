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

			sendMsgToClient (c, *it);
		}
	}

	return true;
}

bool SERVER::sendMsgToClient (std::string &msg, CLIENT &receiver)
{
	return true;
}

bool SERVER::sendMessageList (CLIENT &receiver)
{
        for(std::list<MESAJ>::iterator it = listamesaje.begin(); it != listamesaje.end(); it++){
               sendMsgToClient ((*it).getName(), receiver);
               sendMsgToClient ((*it).getComment(), receiver);
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

// do all the communication with the clients in this thread function
void client_Communication (SERVER *server_p, int sockfd)
{
        server_p->mtxLock();
        server_p->mtxUnlock();
}