//////////////////////////  Server2.c ////////////////
/*Current server 2*/
#include<io.h>
#include<stdio.h>
#include<winsock2.h>

#define MY_PORT		8989
#define MAXBUF		256

void lower(char *a); /*change to lowercase character by character through passing by reference*/
void reverse(char *c,  int x); /*reverse by passing through reference*/

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

	/*---forever... ---*/
    struct sockaddr_in client_addr;
	int addrlen=sizeof(client_addr);
    while(1){
        clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);

        /*inet_ntoa is used convert IP address to binary form and store in struct sockaddr_in self*/
        printf("\nIP address of client: %s", inet_ntoa(client_addr.sin_addr));  //print IP address
        /*Translate port to print on host screen*/
        printf("\nTargeted port number: %d\n", (int) ntohs(client_addr.sin_port));
        puts("Waiting for incoming connections...");
        /*---accept a connection (creating a data pipe)---*/
        int p;
        while (1)
        {
            //empty buffer
            memset(buffer, 0, sizeof(buffer));
            p = recv(clientfd,buffer,MAXBUF,0);

            //print IP address and Port
            if (buffer[1]!='\n'){
                /*inet_ntoa is used convert IP address to binary form and store in struct sockaddr_in self*/
                printf("\nIP address of client: %s", inet_ntoa(client_addr.sin_addr));  //print IP address
                /*Translate port to print on host screen*/
                printf("\nTargeted port number: %d", (int) ntohs(client_addr.sin_port));
                printf("\nLength of string: %d\n", strlen(buffer)); /*display length of string*/
            }

            buffer[p]='\0'; /*set terminating character*/
            lower(buffer); /*to change input to lowercase*/

            //for exit
            int flag=1;
            char exit[] = "exit server";
            int h=0; //count words
            while (exit[h]!='\0' && buffer[h]!='\0') { /*if input is "exit server", flag =1*/
                if (exit[h]!=buffer[h]) {
                    flag=0; /*found difference in characters. Input is not "exit server"*/
                    break;
                }
                ++h; /*increase by 1 to move on to next character*/
            }
            if (flag==1) { /*if input is "exit server", then break out of while loop*/
                printf("\nConnection closed");
                goto closing;
            }

            //for reverse
            reverse(buffer,p);
            char buffer1[p + 1];
            for (int i = 0; buffer[i] != '\0'; ++i) {
                buffer1[i] = buffer[i];
            }
            buffer1[p] = '\r'; // add carriage return
            buffer1[p + 1] = '\n'; //add newline
            buffer1[p + 2] = '\0'; //set terminating character
            send(clientfd, buffer, p , 0);
            //p = recv(clientfd,buffer,MAXBUF,0);
        }//end while
        /*---close connection---*/
        closing:
            close(clientfd);
    }//end while
    
	/*---clean up (should never get here!)---*/
	close(sockfd);
        WSACleanup();
	return 0;
}//end main

void lower(char *a) { /*change to lowercase character by character through passing by reference*/
    for(int i=0;*(a+i)!='\0';++i) {
        if(*(a+i)>='A' && *(a+i)<='Z') {
            *(a+i)=*(a+i)+32;
        }
    }
} //end lower function

void reverse(char *c, int x) { /*reverse by passing through reference*/
    int m=x-1; //discard '\0'
    int q=0;
    int count=0, j=0;
    char temp; //temporary variable to store character
    //start from 0 and end before terminating character
    for(;j<m;j++,m--) {
        temp=*(c+j);
        *(c+j)=*(c+m);
        *(c+m)=temp;
    }
} //end reverse function