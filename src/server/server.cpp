#include "server.h"

SERVER::SERVER ()
{

}

SERVER::~SERVER ()
{

}

bool SERVER::addMessage (MESAJ &m)
{
	return false;
}

bool SERVER::addClient (CLIENT &c)
{
	return false;
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

bool SERVER::sendMsgToClient (std::string msg, CLIENT &receiver)
{
	return true;
}
