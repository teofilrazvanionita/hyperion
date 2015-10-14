#include "client.h"

CLIENT::CLIENT()
{

}

CLIENT::~CLIENT()
{

}

bool CLIENT::setCryptInfo (CRYPTO &ci)
{
	cryptinfo = ci;
	return true;
}

bool CLIENT::setSockFd (int &sfd)
{
	sockfd = sfd;
	return true;
}

CLIENT& CLIENT::operator = (CLIENT &c)
{
	if (this != &c){
		cryptinfo = c.getCI();
		sockfd = c.getSFD();
	}

	return *this;
}

CRYPTO& CLIENT::getCI ()
{
	return cryptinfo;
}

int& CLIENT::getSFD ()
{
	return sockfd;
}

// constructorul de copiere
CLIENT::CLIENT(CLIENT &c)
{
	cryptinfo = c.getCI();
	sockfd = c.getSFD();
}
