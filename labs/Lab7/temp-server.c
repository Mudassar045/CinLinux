/*
   WEB SERVER
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>

#define EOL "\r\n"
#define EOL_SIZE 2

typedef struct
{
    char *ext;
    char *mediatype;
} extn;

//Possible media types
extn extensions[] = {
    {"gif", "image/gif"},
    {"txt", "text/plain"},
    {"jpg", "image/jpg"},
    {"jpeg", "image/jpeg"},
    {"png", "image/png"},
    {"ico", "image/ico"},
    {"zip", "image/zip"},
    {"gz", "image/gz"},
    {"tar", "image/tar"},
    {"htm", "text/html"},
    {"html", "text/html"},
    {"php", "text/html"},
    {"pdf", "application/pdf"},
    {"zip", "application/octet-stream"},
    {"rar", "application/octet-stream"},
    {0, 0}};

/*
 A helper function
 */
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

/*
 A helper function
 */
int get_file_size(int fd)
{
    struct stat stat_struct;
    if (fstat(fd, &stat_struct) == -1)
        return (1);
    return (int)stat_struct.st_size;
}

/*
 A helper function
 */
void send_response(int fd, char *msg)
{
    int len = strlen(msg);
    if (write(fd, msg, len) == -1)
    {
        printf("Error in send\n");
    }
}

/*
 This function recieves the buffer
 until an "End of line(EOL)" byte is recieved
 */
int recv_new(int fd, char *buffer)
{
    char *p = buffer;              // Use of a pointer to the buffer rather than dealing with the buffer directly
    int eol_matched = 0;           // Use to check whether the recieved byte is matched with the buffer byte or not
    while (recv(fd, p, 1, 0) != 0) // Start receiving 1 byte at a time
    {
        if (*p == EOL[eol_matched]) // if the byte matches with the first eol byte that is '\r'
        {
            ++eol_matched;
            if (eol_matched == EOL_SIZE) // if both the bytes matches with the EOL
            {
                *(p + 1 - EOL_SIZE) = '\0'; // End the string
                return (strlen(buffer));    // Return the bytes recieved
            }
        }
        else
        {
            eol_matched = 0;
        }
        p++; // Increment the pointer to receive next byte
    }
    return (0);
}

/*
 A helper function: Returns the web root location.
 */
char *webroot()
{
    // open the file "conf" for reading
    FILE *in = fopen("conf", "rt");
    // read the first line from the file
    char buff[1000];
    fgets(buff, 1000, in);
    // close the stream
    fclose(in);
    char *nl_ptr = strrchr(buff, '\n');
    if (nl_ptr != NULL)
        *nl_ptr = '\0';
    return strdup(buff);
}
/*
 This function parses the HTTP requests,
 arrange resource locations,
 check for supported media types,
 serves files in a web root,
 sends the HTTP error codes.
 */
int connection(int fd)
{
    char request[500], resource[500], *ptr;
    int fd1, length;
    if (recv_new(fd, request) == 0)
    {
        printf("Recieve Failed\n");
    }
    printf("%s\n", request);
    // Check for a valid browser request
    ptr = strstr(request, " HTTP/");
    if (ptr == NULL)
    {
        printf("NOT HTTP !\n");
    }
    else
    {
        *ptr = 0;
        ptr = NULL;

        if (strncmp(request, "GET ", 4) == 0)
        {
            ptr = request + 4;
            printf("%s",request);
        }
        if (ptr == NULL)
        {
            printf("Unknown Request ! \n");
        }
        else
        {
            if (ptr[strlen(ptr) - 1] == '/')
            {
                strcat(ptr, "index.html");
            }
            strcpy(resource, webroot());
            strcat(resource, ptr);
            char *s = strchr(ptr, '.');
            int i;
            for (i = 0; extensions[i].ext != NULL; i++)
            {
                if (strcmp(s + 1, extensions[i].ext) == 0)
                {
                    fd1 = open(resource, O_RDONLY, 0);
                    printf("Opening \"%s\"\n", resource);
                    if (fd1 == -1)
                    {
                        printf("404 File not found Error\n");
                        send_response(fd, "Content-Type: text/html;\n\n");
                        send_response(fd, "HTTP/1.1 404 Not Found\r\n");
                        send_response(fd, "Server : Web Server in c\r\n\r\n");
                        send_response(fd, "<html><head><title>404 Not Found</head></title>");
                        send_response(fd, "<body><p>404 Not Found: The requested resource could not be found!</p></body></html>");
                    }
                    else
                    {
                        printf("200 OK, Content-Type: %s\n\n",extensions[i].mediatype);
                        send_response(fd, "HTTP/1.1 200 OK\r\n");
                        send_response(fd, "Content-Type: text/html\n\n");
                        
                        if (ptr == request + 4) // if it is a GET request
                        {
                            if ((length = get_file_size(fd1)) == -1)
                                printf("Error in getting size !\n");
                            //sendfile(fd, fd1, 0,length);
                            //printf("datasize: %d\n",length);
                            
                            size_t total_bytes_sent = 0;
                            ssize_t bytes_sent;
                            while (total_bytes_sent < length)
                            {
                                //Zero copy optimization, moving data in kernal space
                                if ((bytes_sent = sendfile(fd, fd1, 0,length - total_bytes_sent)) <= 0)
                                {
                                    if (errno == EINTR || errno == EAGAIN)
                                    {
                                        continue;
                                    }
                                    perror("sendfile");
                                    return -1;
                                }
                                total_bytes_sent += bytes_sent;
                            }
                        }
                    }
                    break;
                }
                int size = sizeof(extensions) / sizeof(extensions[0]);
                if (i == size - 2)
                {
                    printf("415 Unsupported Media Type\n");
                    send_response(fd, "Content-Type: text/html\n\n");
                    send_response(fd, "HTTP/1.1 415 Unsupported Media Type\r\n");
                    send_response(fd, "<html><head><title>415 Unsupported Media Type</head></title>");
                    send_response(fd, "<body><p>415 Unsupported Media Type!</p></body></html>");
                }
            }
        }
    }
    shutdown(fd, SHUT_RDWR);
    close(fd);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, pid;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    if (argc < 2)
    {
        fprintf(stderr, "md-webserver: port is empty or not provided\n");
    }
    printf("Server@%s :", argv[1]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        fprintf(stderr,"md-webserver: unable to open '%s' ",argv[1]);
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        fprintf(stderr,"md-webserver: unable to bind '127.0.0.1' address");
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

  /*
  Server runs forever, forking off a separate process for each connection.
  */
    while (1)
    {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0)
            fprintf(stderr,"md-webserver: unable to accept new request");
        pid = fork();
        if (pid < 0)
            fprintf(stderr,"md-webserver: unable to invoke child process");
        if (pid == 0)
        {
            close(sockfd);
            connection(newsockfd);
            exit(0);
        }
        else
            close(newsockfd);
    } // WHILE_END
    close(sockfd);
    return 0; 
}