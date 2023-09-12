//////////////////////////  Server1.c ////////////////

#include<io.h>
#include<stdio.h>
#include<winsock2.h>

#define MY_PORT		8989
#define MAXBUF		256

int main(int argc , char *argv[])
{
    WSADATA wsa;
    SOCKET sockfd , clientfd;
    	struct sockaddr_in self;
	char buffer[MAXBUF];

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
     
    printf("Initialised.\n");

	/*---create streaming socket---*/
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Socket");
		exit(errno);
	}

        printf("Socket created.\n");

	/*---initialize address/port structure---*/
	/* bzero(&self, sizeof(self));*/
	self.sin_family = AF_INET;
	self.sin_port = htons(MY_PORT);
	self.sin_addr.s_addr = INADDR_ANY;

	/*---assign a port number to the socket---*/
    if ( bind(sockfd, (struct sockaddr*)&self, sizeof(self)) != 0 )
	{
		perror("socket--bind");
		exit(errno);
	}

        puts("Bind done");

	/*---make it a "listening socket"---*/
	if ( listen(sockfd, 20) != 0 )
	{
		perror("socket--listen");
		exit(errno);
	}
        
        puts("Waiting for incoming connections...");

	/*---forever... ---*/
	while (1)
	{	struct sockaddr_in client_addr;
		int addrlen=sizeof(client_addr);

		/*---accept a connection (creating a data pipe)---*/
		clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
        int p;
        p=recv(clientfd,buffer,MAXBUF,0);

        /*converting input to lowercase by checking character by character*/
        for(int i=0;buffer[i]!='\0';++i) {
            if(buffer[i]>='A' && buffer[i]<='Z') {
                buffer[i]=buffer[i]+32;
            }
        }

        /*reverse input*/
        int q=0; 
        char temp; /*temporary variable to store character*/
        q=strlen(buffer); /*use to calculate length of buffer*/
        int r=q-1; /*minus terminating null character*/

        for(int j=0;j<strlen(buffer)/2;j++) {/*change the position on input. Last character becomes first character.*/
            temp=buffer[j];
            buffer[j]=buffer[r];
            buffer[r--]=temp;
        }
		
		send(clientfd, buffer, p, 0);
		/*---close connection---*/
		close(clientfd);
	}

	/*---clean up (should never get here!)---*/
	close(sockfd);
        WSACleanup();
	return 0;
}

