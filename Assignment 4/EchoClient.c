/*ECHOCLIENT*/
#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#include <string.h>

#define MY_PORT	8989
#define MAXBUF 256
int exit1(char *b); /*exit server*/

int main (void){
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0){
        printf("Failed to initialize Winsock library.\n");
        return 1;
    }

    /*socket*/
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET){
        printf("Failed to create socket.\n");
        WSACleanup();
        return 1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(MY_PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    /*connect*/
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Failed to connect to server.\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    /*initialised*/
    int m = 0;
    char buffer[MAXBUF];
    int sending = 0;
    int len=0, flop=0;
    char server_reply[MAXBUF];

    /*while loop - send and receive*/
    while(1){
        memset(buffer,0,MAXBUF); /*clear buffer*/
        printf("\nPlease put in some message: ");
        fgets(buffer, MAXBUF, stdin); /*get input*/

        flop = exit1(buffer);
        if (flop==1) { /*if user input "exit client", connection is disconnected*/
            printf("Client connection terminated");
            closesocket(sock);
            break;
        }

        for (int i=0;buffer[i]!='\0';i++){
            if(buffer[i] == '\n'){ /*Change newline to terminating null characters*/
                buffer[i] = 0;
            } //end nested if
        }//end for loop

        sending = send(sock, buffer, strlen(buffer), 0); /*send message*/
        if (sending < 0){
            printf("Failed to send data.\n");
        }
        
        len = recv(sock, server_reply, MAXBUF, 0); /*Receive a reply from the server*/
        if (len > 0){ /*if message reveived then, print it*/
            server_reply[len] = '\0';
            printf("Received: %s", server_reply);
        }
        else if (len == 0){
            printf("Connection closed by server.\n");
        }
        else{ /*if message failed to receive*/
            printf("Failed to receive data.\n");
        }
    }//end while

    /*close connection*/
    closesocket(sock);
    WSACleanup();
    return 0;
}

int exit1(char *b) {  /*check if client input "exit client"*/
    int flag=1;
    char exit[] = "exit client";
    int h=0; //count words
    while (exit[h]!='\0' && *(b+h)!='\0') {
        if (exit[h]!=*(b+h)) {
            flag=0; //not the same
            break;
        }
        ++h; /*increase by 1 to move on to next character*/
    }
    return flag; 
}
