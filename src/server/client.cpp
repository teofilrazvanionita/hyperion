#include "client.h"

// default contructor
CLIENT::CLIENT ()
{

}

// destructor
CLIENT::~CLIENT()
{

}

// copy constructor
CLIENT::CLIENT (CLIENT &c)
{
	cryptinfo = c.getCI();
	sockfd = c.getSFD();
}

// parameters constructor
CLIENT::CLIENT (CRYPTO &ci, int &sfd)
{
	cryptinfo = ci;
	sockfd = sfd;
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


