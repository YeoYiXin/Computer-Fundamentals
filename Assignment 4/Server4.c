//////////////////////////  Server4.c ////////////////
#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#include <time.h>

#define MY_PORT		8989
#define MAXBUF		256

void lower(char *a); /*change input to lowercase*/
int exit1(char *b); /*check if client send "exit server"*/
void reverse(char *c,  int x); /*reversing the inputs*/
int special_command(char g[]); /*to check for similarity in names*/
int special_command1(char d[]); /*to check for similarity in names*/
int special_command2(char e[]); /*check if its "time "*/
void count(char *f, int a); /*to obtain date*/
void date(char *m, int q); /*to obtain date just like in Server3*/
int check_pst(char c1[]); /*check if its "time pst"*/
int check_mst(char c2[]); /*check if its "time mst"*/
int check_cst(char c3[]); /*check if its "time cst"*/
int check_est(char c4[]); /*check if its "time est"*/
int check_gmt(char c5[]); /*check if its "time gmt"*/
int check_cet(char c6[]); /*check if its "time cet"*/
int check_msk(char c7[]); /*check if its "time msk"*/
int check_jst(char c8[]); /*check if its "time jst"*/
int check_aedt(char c9[]); /*check if its "time aedt"*/

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
    struct sockaddr_in client_addr;
	int addrlen=sizeof(client_addr);
    while(1){
    clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);

     /*inet_ntoa is used convert IP address to binary form and store in struct sockaddr_in self*/
    printf("\nIP address of client: %s", inet_ntoa(client_addr.sin_addr));  //print IP address
    /*Translate port to print on host screen*/
    printf("\nTargeted port number: %d", (int) ntohs(client_addr.sin_port));
	/*---accept a connection (creating a data pipe)---*/
    int p;
    int flag=0, timing=0, check=0, first=0, second=0, third=0, fourth=0, fifth=0, sixth=0, seventh=0, eighth=0, ninth=0;
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

        //for lower
        lower(buffer);
        buffer[p]='\0'; //set terminating character
        //for exit
        int flop = exit1(buffer);
        if (flop==1){ /*if input is "exit server", then break out of while loop*/
            printf("\nConnection closed");
            goto closing;
        }

        if ((timing = special_command(buffer))==1){   /*Malaysia time - GMT +8*/
            date(buffer, 0); /*if user input "date"*/
            int q=strlen(buffer); /*check for length and then send to client*/
            send(clientfd, buffer, q, 0);
        }

        if ((flag = special_command1(buffer))==1){   /*Malaysia time - GMT +8*/
            count(buffer, 0); /*if user input "time"*/
            int q=strlen(buffer); /*check for length and then send to client*/
            send(clientfd, buffer, q, 0);
        }
        
        else if ((first = check_pst(buffer))==1){   /*8+8=16*/
            count(buffer, 16); /*if user input "time pst"*/
            int q=strlen(buffer); /*check for length and then send to client*/
            send(clientfd, buffer, q, 0);
        }

        else if ((second = check_mst(buffer))==1){ /*8+7=15*/
            count(buffer, 15); /*if user input "time mst"*/
            int q=strlen(buffer); /*check for length and then send to client*/
            send(clientfd, buffer, q, 0);
        }

        else if ((third = check_cst(buffer))==1){ /*8+6=14*/
            count(buffer, 14);  /*if user input "time cst"*/
            int q=strlen(buffer); /*check for length and then send to client*/
            send(clientfd, buffer, q, 0);
        }

        else if ((fourth = check_est(buffer))==1){ /*8+5=13*/
            count(buffer, 13);  /*if user input "time est"*/
            int q=strlen(buffer); /*check for length and then send to client*/
            send(clientfd, buffer, q, 0);
        }

        else if ((fifth = check_gmt(buffer))==1){ /*0+8=8*/
            count(buffer, 8);  /*if user input "time gmt"*/
            int q=strlen(buffer); /*check for length and then send to client*/
            send(clientfd, buffer, q, 0);
        }

        else if ((sixth = check_cet(buffer))==1){ /*8-1=7*/
            count(buffer, 7);  /*if user input "time cet"*/
            int q=strlen(buffer); /*check for length and then send to client*/
            send(clientfd, buffer, q, 0);
        }

        else if ((seventh = check_msk(buffer))==1){ /*8-3=5*/
            count(buffer, 5);    /*if user input "time msk"*/
            int q=strlen(buffer); /*check for length and then send to client*/
            send(clientfd, buffer, q, 0);
        }

        else if ((eighth = check_jst(buffer))==1){ /*8-9=-1*/
            count(buffer, -1);  /*if user input "time jst"*/
            int q=strlen(buffer); /*check for length and then send to client*/
            send(clientfd, buffer, q, 0);
        }

        else if ((ninth = check_aedt(buffer))==1){ /*8-11=-3*/
            count(buffer, -3);  /*if user input "time aedt"*/
            int q=strlen(buffer); /*check for length and then send to client*/
            send(clientfd, buffer, q, 0);
        }

        else if (((check=special_command2(buffer))==1) && first==0 && second==0 && third==0 && fourth==0 && fifth==0 & sixth==0 && seventh==0 && eighth==0 && ninth==0){
            char wrong[100] = "ERROR";  /*if user input is wrong after the word "time"*/
            int q = strlen(wrong);
            char buffer[q+2];
            for (int i = 0; wrong[i] != '\0'; ++i) {
                buffer[i] = wrong[i];
            }
            buffer[q] = '\r'; /*carriage return*/
            buffer[q + 1] = '\n'; /*add newline*/
            buffer[q + 2] = '\0'; /*set terminating character*/
            send(clientfd, buffer, q + 2, 0);
        }//end if
   
        else if (timing==0 && flag==0 && check==0 && first==0 && second==0 && third==0 && fourth==0 && fifth==0 & sixth==0 && seventh==0 && eighth==0 && ninth==0){ //for reverse
            reverse(buffer,p); /*reversing input*/
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

int exit1(char *b) {  /*check if client input "exit server"*/
    int flag=1;
    char exit[] = "exit server";
    int h=0; //count words
    while (exit[h]!='\0' && *(b+h)!='\0'){
        if (exit[h]!=*(b+h)){ /*found difference in characters. Input is not "exit server"*/
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

int special_command(char g[]){  /*check if client input "date"*/
    int flag=1;

    int k = strlen(g);
        
    char comm[10]="date";
    int h=0; //count words
    while (comm[h]!=0 && g[h]!=0) {
        if (comm[h]!=g[h]) {  /*found difference in characters. Input is not "exit server"*/
            flag=0; 
            break;
        }
        ++h; /*increase by 1 to move on to next character*/
    }
   return flag;
}

int special_command1(char d[]) { //check if user input date
    int flag=1;

    int k = strlen(d);
    int m = strlen("time");
    if (k!=m){ /*if length not the same, then return*/
        flag=0;
        return flag;
    }

    if (k>m){ /*if length larger then "time", then return*/
        flag=0;
        return flag;
    }
        
    char comm[10]="time";
    int h=0; //count words
    while (comm[h]!=0 && d[h]!=0) {
        if (comm[h]!=d[h]) {
            flag=0; 
            break;
        }
        ++h; /*increase by 1 to move on to next character*/
    }
   return flag;
}

int special_command2(char e[]) {
    int flag=1;

    char comm[10]="time ";
    int h=0; //count words
     while (comm[h]!=0 && e[h]!=0) {
        if (comm[h]!=e[h]) {
            flag=0; 
            break;
        }
        ++h; /*increase by 1 to move on to next character*/
    }
   return flag;
}

int check_pst(char c1[]) {
    int flag=1;

    char comm[10]="time pst";
    int h=0; //count words
    while (comm[h]!=0 && c1[h]!=0) {
        if (comm[h]!=c1[h]) {
            flag=0; //not the same
            break;
        }
        ++h; /*increase by 1 to move on to next character*/
    }
   return flag;
}

int check_mst(char c2[]) {
    int flag=1;

    char comm[10]="time mst";
    int h=0; //count words
    while (comm[h]!=0 && c2[h]!=0) {
        if (comm[h]!=c2[h]) {
            flag=0; //not the same
            break;
        }
        ++h; /*increase by 1 to move on to next character*/
    }
   return flag;
}

int check_cst(char c3[]) {    
    int flag=1;

    char comm[10]="time cst";
    int h=0; //count words
    while (comm[h]!=0 && c3[h]!=0) {
        if (comm[h]!=c3[h]) {
            flag=0; //not the same
            break;
        }
        ++h; /*increase by 1 to move on to next character*/
    }
   return flag;
}

int check_est(char c4[]) {
    int flag=1;

    char comm[10]="time est";
    int h=0; //count words
    while (comm[h]!=0 && c4[h]!=0) {
        if (comm[h]!=c4[h]) {
            flag=0; //not the same
            break;
        }
        ++h; /*increase by 1 to move on to next character*/
    }
   return flag;
}

int check_gmt(char c5[]) {
    int flag=1;

    char comm[10]="time gmt";
    int h=0; //count words
    while (comm[h]!=0 && c5[h]!=0) {
        if (comm[h]!=c5[h])  {
            flag=0; //not the same
            break;
        }
        ++h; /*increase by 1 to move on to next character*/
    }
   return flag;
}

int check_cet(char c6[]) {
    int flag=1;
    
    char comm[10]="time cet";
    int h=0; //count words
    while (comm[h]!=0 && c6[h]!=0) {
        if (comm[h]!=c6[h]) {
            flag=0; //not the same
            break;
        }
        ++h; /*increase by 1 to move on to next character*/
    } 
   return flag;
}

int check_msk(char c7[]) {
    int flag=1;
 
    char comm[10]="time msk";
    int h=0; //count words
    while (comm[h]!=0 && c7[h]!=0) {
        if (comm[h]!=c7[h]) {
            flag=0; //not the same
            break;
        }
        ++h; /*increase by 1 to move on to next character*/
    }
   return flag;
}

int check_jst(char c8[]) {
    int flag=1;

    char comm[10]="time jst";
    int h=0; //count words
    while (comm[h]!=0 && c8[h]!=0) {
        if (comm[h]!=c8[h]) {
            flag=0; //not the same
            break;
        }
        ++h; /*increase by 1 to move on to next character*/
    }
   return flag;
}

int check_aedt(char c9[]) {
    int flag=1;
 
    char comm[11]="time aedt";
    int h=0; //count words
    while (comm[h]!=0 && c9[h]!=0) {
        if (comm[h]!=c9[h]) {
            flag=0; //not the same
            break;
        }
        ++h; /*increase by 1 to move on to next character*/
    }
   return flag;
}

void date(char *m, int q){
    time_t t;  /*initialised t with data type time_t*/
    t = time(NULL); //to get current time
    struct tm *tdy = localtime(&t); /*to use tm members*/
    int hours, minutes, seconds, day, month, year, week;          
    week = tdy->tm_wday;  //to get current days
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

    char *printout;
    hours = tdy->tm_hour;         /*get hours since midnight (0-23)*/
    minutes =tdy->tm_min;        /*get minutes passed after the hour (0-59)*/
    seconds = tdy->tm_sec;        /*get seconds passed after a minute (0-59)*/

    day = tdy->tm_mday;            /*get day of month (1 to 31)*/
    year = tdy->tm_year + 1900;   /*get year since 1900*/

    /*to store all the information in a character array variable*/
    sprintf(printout, "%s %s %02d %02d:%02d:%02d %d", week1, month1, day, hours, minutes, seconds, year);
    int w=0;
    w = strlen(printout);  /*obtain length of the string*/
    for (int i = 0; printout[i] != '\0'; ++i) 
    {
        *(m+i) = printout[i];
    }
    *(m+w) = '\r'; /*carriage return*/
    *(m+w+1) = '\n'; /*add newline*/
    *(m+w+2) = '\0';  /*set terminating character*/
}

void count(char *f, int a) {
    // Get the current time in the local time zone
    time_t t = time(NULL); /*initialised t with data type time_t and set as current time*/
    struct tm *tm = localtime(&t); /*to use struct tm members*/

    /*minus accordingly to the value passed into the integer*/
    tm->tm_hour -= a;

    /*Ensure that the time does not change the day*/
    if (tm->tm_hour > 23) {
        tm->tm_hour -= 24;
    } else if (tm->tm_hour < 0) {
        tm->tm_hour += 24;
    }

    /*Store the formatted time string in a character array*/
    char printout[9];
    sprintf(printout, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
    int w=0;
    a = strlen(printout);
    for (int i = 0; printout[i] != '\0'; ++i) 
    {
        *(f+i) = printout[i];
    }
    *(f+a) = '\r'; /*carriage return*/
    *(f+a+1) = '\n'; /*add newline*/
    *(f+a+2) = '\0'; /*set terminating character*/
}