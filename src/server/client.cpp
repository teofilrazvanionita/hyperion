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
