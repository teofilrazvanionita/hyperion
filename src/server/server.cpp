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

std::string& SERVER::decryptMSG (std::string &msg, CLIENT &client)
{

}

std::string& SERVER::encryptMSG (std::string &msg)
{

}
