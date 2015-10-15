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
CLIENT::CLIENT (const CLIENT &c)
{
	cryptinfo = ((CLIENT &)c).getCI();
	sockfd = ((CLIENT &)c).getSFD();
}

// parameters constructor
CLIENT::CLIENT (CRYPTO &ci, int &sfd)
{
	cryptinfo = ci;
	sockfd = sfd;
}

bool CLIENT::setCI (CRYPTO &ci)
{
	cryptinfo = ci;
	return true;
}

bool CLIENT::setSFD (int &sfd)
{
	sockfd = sfd;
	return true;
}

// assignment operator
CLIENT& CLIENT::operator = (const CLIENT &c)
{
	if (this != &c){
		cryptinfo = ((CLIENT &)c).getCI();
		sockfd = ((CLIENT &)c).getSFD();
	}

	return *this;
}

bool CLIENT:: operator == (CLIENT &c){
	
	if(this != &c){
		if ((cryptinfo == c.getCI()) && (sockfd == c.getSFD()))
			return true;
	}else
		return true;

	return false;
}

bool CLIENT::operator != (CLIENT &c)
{
	return !(*this == c);
}

CRYPTO& CLIENT::getCI ()
{
	return cryptinfo;
}

int& CLIENT::getSFD ()
{
	return sockfd;
}

std::string& CLIENT::getNume ()
{
	return nume;
}

