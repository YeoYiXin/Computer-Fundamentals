//////////////////////////  Server3.c ////////////////

#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#include <time.h>

#define MY_PORT		8989
#define MAXBUF		256

void lower(char *a); /*change to lowercase character by character through passing by reference*/
int exit1(char *b); /*to exit server if client send "exit server"*/
void reverse(char *c,  int x); /*reverse by passing through reference*/
int special_command(char *d); /*to check if client send "date"*/
int main(int argc , char *argv[])
{
    WSADATA wsa;
    SOCKET sockfd , clientfd;
    struct sockaddr_in self;
	char buffer[MAXBUF];
    char printout[MAXBUF];

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
    struct sockaddr_in client_addr;
	int addrlen=sizeof(client_addr);
    while (1){
        clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
        /*inet_ntoa is used convert IP address to binary form and store in struct sockaddr_in self*/
        printf("\nIP address of client: %s", inet_ntoa(client_addr.sin_addr));  //print IP address
        /*Translate port to print on host screen*/
        printf("\nTargeted port number: %d", (int) ntohs(client_addr.sin_port));

        /*---accept a connection (creating a data pipe)---*/
        int p;
        while (1)
        {
            //empty buffer
            memset(buffer, 0, MAXBUF);
            p = recv(clientfd,buffer,MAXBUF,0);

            //print IP address and Port
            if (buffer[1]!='\n'){
                /*inet_ntoa is used convert IP address to binary form and store in struct sockaddr_in self*/
                printf("\n\nIP address of client: %s", inet_ntoa(client_addr.sin_addr));  //print IP address
                /*Translate port to print on host screen*/
                printf("\nTargeted port number: %d", (int) ntohs(client_addr.sin_port));
                printf("\nLength of string: %d", strlen(buffer)); /*display length of string*/
            }

            lower(buffer); /*to change input to lowercase*/
            buffer[p]='\0'; /*set terminating character*/

            //for exit
            int flop = exit1(buffer);
            if (flop==1) { /*if input is "exit server", then break out of while loop*/
                printf("\nConnection closed");
                goto closing;
            }
            
            int flag = special_command(buffer); /*check whether it is "date"*/
            if (flag==1) {
                time_t t; /*initialised t with data type time_t*/
                t = time(NULL); //to get current time
                struct tm *tdy = localtime(&t); /*to use tm members*/
                int hours, minutes, seconds, day, month, year, week;
                week = tdy->tm_wday +1;       /*to get current days*/
                char *week1;
                switch (week){ /*print day of week in string*/
                    case 1: {
                        week1 = "Sun"; 
                        break;
                    }
                    case 2:{
                        week1 = "Mon"; 
                        break;
                    }
                    case 3:{
                        week1 = "Tues"; 
                        break;
                    }
                    case 4:{
                        week1 = "Wed"; 
                        break;
                    }
                    case 5:{
                        week1 = "Thurs"; 
                        break;
                    }
                    case 6:{
                        week1 = "Fri"; 
                        break;
                    }
                    case 7:{
                        week1 = "Sat"; 
                        break;
                    }
                    default: week1 = "Wrong week of the day!"; break;
                }//end switch week

                month = tdy->tm_mon + 1;  /*get month of year (0 to 11)*/
                char *month1;
                switch (month){ /*print month in string*/
                    case 1: {
                        month1 = "Jan"; 
                        break;
                    }
                    case 2:{
                        month1 = "Feb";
                        break;
                    }
                    case 3:{
                        month1 = "Mar";
                        break;
                    }
                    case 4:{
                        month1 = "Apr"; 
                        break;
                    }
                    case 5:{
                        month1 = "May"; 
                        break;
                    }
                    case 6:{
                        month1 = "June"; 
                        break;
                    }
                    case 7:{
                        month1 = "July";
                        break;
                    }
                    case 8:{
                        month1 = "Aug"; 
                        break;
                    }
                    case 9:{
                        month1  = "Sep";
                        break;
                    }
                    case 10:{
                        month1 = "Oct"; 
                        break;
                    }
                    case 11:{
                        month1 = "Nov";
                        break;
                    }
                    case 12:{
                        month1 = "Dec"; 
                        break;
                    }
                }//end switch week

                hours = tdy->tm_hour;         /*get hours since midnight (0-23)*/
                minutes =tdy->tm_min;        /*get minutes passed after the hour (0-59)*/
                seconds = tdy->tm_sec;        /*get seconds passed after a minute (0-59)*/
        
                day = tdy->tm_mday;            /*get day of month (1 to 31)*/
                year = tdy->tm_year + 1900;   /*get year since 1900*/

                /*to store all the information in a character array variable*/
                sprintf(printout, "%s %s %02d %02d:%02d:%02d %d GMT", week1, month1, day, hours, minutes, seconds, year);

                int q = strlen(printout); /*obtain length of the string*/
                char buffer1[q + 2];
                for (int i = 0; printout[i] != '\0'; ++i) {
                    buffer1[i] = printout[i];
                }
                buffer1[q] = '\r'; /*carriage return*/
                buffer1[q + 1] = '\n'; /*add newline*/
                buffer1[q + 2] = '\0'; /*set terminating character*/
                send(clientfd, buffer1, q + 2, 0);
            }
            else
            {
                //for reverse
                reverse(buffer,p);
                char buffer1[p + 2];
                for (int i = 0; buffer[i] != '\0'; ++i) {
                    buffer1[i] = buffer[i];
                }
                buffer1[p] = '\r'; /*carriage return*/
                buffer1[p + 1] = '\n'; /*add newline*/
                buffer1[p + 2] = '\0';  /*set terminating character*/
                send(clientfd, buffer1, p + 2, 0);
            }
        }//end while
        /*---close connection---*/
        closing:
            close(clientfd);
    }
    
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

int exit1(char *b) { /*check if client input "exit server"*/
    int flag=1;
    char exit[] = "exit server";
    int h=0; //count words
    while (exit[h]!='\0' && *(b+h)!='\0') {
        if (exit[h]!=*(b+h)) { /*found difference in characters. Input is not "exit server"*/
            flag=0; 
            break;
        }
        ++h; /*increase by 1 to move on to next character*/
    }
    return flag; 
} //end exit function

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

int special_command(char *d) { //check if user input date
    int flag=1;
    char comm[5]="date";
    int h=0; //count words
    while (comm[h]!='\0' && *(d+h)!='\0') {
        if (comm[h]!=*(d+h)) {
            flag=0; //not the same
            break;
        }
        ++h;
    }
   return flag;
}