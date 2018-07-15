/*
Name : Mudassar Ali
Resident: Lahore, Pakistan
Project: FTP using TCP/IP 

Problem Statement: To achieve File transfer using TCP/IP Protocol
*/
/*
	Client Side
	Please pass ip address and port no as command line arguments in the same sequence
	glad.txt file should be already created before you run the program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>

void error(const char *msg);
int main(int argc, char *argv[])
{
    char *filename = argv[3];
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[512];
    if (argc!=4)
    {
        fprintf(stderr, "ftp-client: Invalid paramenters: Usage: %s hostname port filename\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ftp-client: Unable to open socket\n");
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "ftp-client: Unable to find host\n");
        exit(0);
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ftp-client: Unable to connect with server, Try again.\n");

    bzero(buffer, 512);

    FILE *f;

    int words = 0;
    char c;
    f = fopen(filename, "r");
    if(f==NULL)
    {
        fprintf(stderr,"ftp-client: Unable to load '%s' file or directory is not available in client directory\n",filename);
    }
    while ((c = getc(f)) != EOF) //Counting No of words in the file
    {
        fscanf(f, "%s", buffer);
        if (isspace(c) || c == '\t')
            words++;
    }
    //printf("Words = %d \n"  , words);	//Ignore

    write(sockfd, &words, sizeof(int));
    rewind(f);

/*
    fseek(f, 0L, SEEK_END); // tells size of the file. Not rquired for the functionality in code.
    int sz = ftell(f);      //Just written for curiosity.
    printf("Size is %d \n", sz);
    rewind(f);
*/

    char ch;
    while (ch != EOF)
    {

        fscanf(f, "%s", buffer);
        //printf("%s\n" , buffer);	//Ignore
        write(sockfd, buffer, 512);
        ch = fgetc(f);
    }
    printf("ftp-client: '%s' file was sent successfully to server\n",filename);
    close(sockfd);
    return 0;
}
void error(const char *msg)
{
    perror(msg);
    exit(0);
}