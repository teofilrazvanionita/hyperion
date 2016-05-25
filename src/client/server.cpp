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
SERVER::SERVER (const SERVER &s)
{
	cryptinfo = ((SERVER &)s).getCI();
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
SERVER & SERVER::operator = (const SERVER &s)
{
	if (this != &s)
		cryptinfo = ((SERVER &)s).getCI();

	return *this;
}

bool SERVER:: operator == (const SERVER &s){
	
	if(this != &s){
		if (cryptinfo == ((SERVER &)s).getCI())
			return true;
	}else
		return true;

	return false;
}

bool SERVER::operator != (const SERVER &s)
{
	return !(*this == s);
}

CRYPTO & SERVER::getCI ()
{
	return cryptinfo;
}
