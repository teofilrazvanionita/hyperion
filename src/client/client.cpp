#include "client.h"

CLIENT::CLIENT (char *IP)
{
	struct sockaddr_in dest_addr;

        name_verified = false;
        
	sockfd = socket (AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		perror ("socket");
		exit (EXIT_FAILURE);	// v. pthread_exit
	}


	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(PORT);
	dest_addr.sin_addr.s_addr = inet_addr(IP);
	memset(&(dest_addr.sin_zero), 0, 8);

	if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr)) == -1){
		if(write (STDERR_FILENO, "Couldn't connect to the server\n", 31) != 31){
                        perror ("write");
                        exit (EXIT_FAILURE);
                }
		if(close(sockfd) == -1){
			perror ("close");
			exit (EXIT_FAILURE);	// v. pthread_exit
		}  
	}
}

CLIENT::~CLIENT ()
{
    
}

void CLIENT::Play ()
{
        server = exchangeCIandName ();
        
        std::thread (writeLoop, this).detach();
        
        std::thread (readLoop, this).detach();
}

SERVER CLIENT::exchangeCIandName ()
{       
        std::string server_pk;
        std::string server_nonce;
        ssize_t br;
        char buf[64];
        char responce;
        
        server_pk = recvPK ();
        server_nonce =  recvNonce ();
        
        sendPK();
        sendNonce();
        
        while(!name_verified){
                if(write (STDOUT_FILENO, "Please select a username: ", 26) != 26){
                    perror ("write");
                    exit (EXIT_FAILURE);
                }
                
                memset (buf, 0, 64);
                
                if((br = read (STDIN_FILENO, buf, 64)) == -1){
                        perror ("read");
                        exit (EXIT_FAILURE);
                }
                
                if(!br){}   //EOF
                
                if(write (sockfd, buf, sizeof(buf)) != sizeof(buf)){
                        perror ("write");
                        exit (EXIT_FAILURE);
                }
                
                if(read (sockfd, &responce, 1) != 1){
                        perror ("read");
                        exit (EXIT_FAILURE);
                }
                
                if(responce == 'Y')
                        name_verified = true;
        }
        
        CRYPTO cryptinfo (server_pk, server_nonce);
        SERVER server (cryptinfo);
        
        return server;
}

void CLIENT::sendPK ()
{
        if(write (sockfd, cryptinfo.getPK().c_str(), crypto_box_PUBLICKEYBYTES ) != crypto_box_PUBLICKEYBYTES){
                perror ("write");
                exit (EXIT_FAILURE);
        }
}

void CLIENT::sendNonce ()
{
        if(write (sockfd, cryptinfo.getNonce().c_str(), crypto_box_NONCEBYTES) != crypto_box_NONCEBYTES){
                perror ("write");
                exit (EXIT_FAILURE);
        }
}

std::string CLIENT::recvPK ()
{
        std::string server_pk;
        char buf[crypto_box_PUBLICKEYBYTES];
        
        memset (buf, 0, crypto_box_PUBLICKEYBYTES);
        
        if(read (sockfd, buf, crypto_box_PUBLICKEYBYTES) != crypto_box_PUBLICKEYBYTES){
                perror ("read");
                exit (EXIT_FAILURE);
        }
        
        server_pk = buf;
        
        return server_pk;
}

std::string CLIENT::recvNonce ()
{
        std::string server_nonce;
        char buf[crypto_box_NONCEBYTES];
        
        memset (buf, 0, crypto_box_NONCEBYTES);
        
        if(read (sockfd, buf, crypto_box_NONCEBYTES) != crypto_box_NONCEBYTES){
                perror ("read");
                exit (EXIT_FAILURE);
        }
        
        server_nonce = buf;
        
        return server_nonce;
}

int CLIENT::getSFD ()
{
        return sockfd;
}

void readLoop (CLIENT *client_p)
{
        char buf[1024];
        ssize_t br;
        
        while(1){
                memset (buf, 0, 1024);
            
                if((br = read (client_p->getSFD(), buf, 1024)) == -1){
                        perror ("read");
                        exit (EXIT_FAILURE);
                }
                if(!br)
                        return;
                if(write(STDOUT_FILENO, buf, br) != br){
                        perror ("write");
                        exit (EXIT_FAILURE);
                }
        }
}

void writeLoop (CLIENT *client_p)
{
        char buf[1024];
        ssize_t br;
        
        while(1){
                memset (buf, 0, 1024);
    
                if((br = read (STDIN_FILENO, buf, 1024)) == -1){
                        perror ("read");
                        exit (EXIT_FAILURE);
                }
                if(!br){
                        //EOF
                        close (client_p->getSFD());
                        return;
                }
                if(write (client_p->getSFD(), buf, br) != br){
                        perror ("write");
                        exit (EXIT_FAILURE);
                }
                
        }
}