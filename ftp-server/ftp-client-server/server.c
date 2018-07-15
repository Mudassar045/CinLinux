/*
Name : Mudassar Ali
Resident: Lahore, Pakistan
Project: FTP using TCP/IP 

Problem Statement: To achieve File transfer using TCP/IP Protocol
*/

/*
	Server Side
	Usage ./sever port-no
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>

void error(const char *msg);
int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[512];

    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;

    int n;
    if (argc < 2)
    {
        fprintf(stderr, "ftp-Server:, please provide\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        fprintf(stderr, "ftp-server: Unable to open port '%d'\n", atoi(argv[1]));

    //creating Socket struct
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //inet_aton("10.0.0.1", &serv_addr.sin_addr);
    //memset(&(serv_addr.sin_zero), '\0', sizeof serv_addr.sin_zero);
    //serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    // binding socket
    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
        error("ftp-server: Unable to bind server information\n");

    listen(sockfd, 5); // listening

    clilen = sizeof(cli_addr); // getting client address
    newsockfd = accept(sockfd,
                       (struct sockaddr *)&cli_addr,
                       &clilen);

    if (newsockfd < 0)
        error("ftp-server: Unable to open new socket for client\n");

    FILE *fp;
    int ch = 0;
    fp = fopen("master.txt", "a");
    int words;
    read(newsockfd, &words, sizeof(int));
    //printf("Passed integer is : %d\n" , words);      //Ignore , Line for Testing
    while (ch != words)
    {
        read(newsockfd, buffer, 512);
        fprintf(fp, " %s", buffer);
        //printf(" %s %d "  , buffer , ch); //Line for Testing , Ignore
        ch++;
    }
    printf("ftp-server: file from client recieved successfully\n");
    printf("ftp-server: new file created is master.txt\n");
    // closing sockets
    close(newsockfd);
    close(sockfd);

    return 0;
}
void error(const char *msg)
{
    perror(msg);
    exit(1);
}