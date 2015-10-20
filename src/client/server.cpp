#include "server.h"

// default contructor
SERVER::SERVER ()
{

}

// destructor
SERVER::~SERVER()
{

}

// copy constructor
SERVER::SERVER (const SERVER &c)
{
	cryptinfo = ((SERVER &)c).getCI();
}

// parameters constructor
SERVER::SERVER (CRYPTO &ci)
{
	cryptinfo = ci;
}

bool SERVER::setCI (CRYPTO &ci)
{
	cryptinfo = ci;
	return true;
}

// assignment operator
SERVER& SERVER::operator = (const SERVER &c)
{
	if (this != &c)
		cryptinfo = ((SERVER &)c).getCI();

	return *this;
}

bool SERVER:: operator == (const SERVER &c){
	
	if(this != &c){
		if (cryptinfo == ((SERVER &)c).getCI())
			return true;
	}else
		return true;

	return false;
}

bool SERVER::operator != (const SERVER &c)
{
	return !(*this == c);
}

CRYPTO& SERVER::getCI ()
{
	return cryptinfo;
}
