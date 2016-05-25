#include "client.h"

CLIENT::CLIENT (char *IP)
{
	struct sockaddr_in dest_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		perror("socket");
		exit(EXIT_FAILURE);	// v. pthread_exit
	}


	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(PORT);
	dest_addr.sin_addr.s_addr = inet_addr(IP);
	memset(&(dest_addr.sin_zero), 0, 8);

	if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr)) == -1){
		if(write(STDERR_FILENO, "Couldn't connect to the server\n", 31) != 31){
                        perror("write");
                        exit(EXIT_FAILURE);
                }
		if(close(sockfd) == -1){
			perror("close");
			exit(EXIT_FAILURE);	// v. pthread_exit
		}  
	}
}

CLIENT::~CLIENT ()
{
    
}

void CLIENT::Play ()
{
    server = exchangeCIandName ();
}

SERVER CLIENT::exchangeCIandName ()
{
    
}