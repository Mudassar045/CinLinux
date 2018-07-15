#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/sendfile.h>
#include <dirent.h>

static int CONNECTION = 0;
#define PORT 9001
#define BYTES 2048

void process_request(char *rq, int fd);
void cannot_do(int sock_fd);
void do_cat(char *file_name, int fd);
void do_html(char *file_name, int fd);
void do_ls(char *dir_name, int fd);
void do_404(int fd);
char *get_filename_ext(const char *filename);
int ends_in_cgi(char *name);
void do_exec(char *comm, int sock_fd);
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
 A helper function
 */
int get_file_size(int fd)
{
	struct stat stat_struct;
	if (fstat(fd, &stat_struct) == -1)
		return (1);
	return (int)stat_struct.st_size;
}
int main()
{

	int create_socket, new_socket;
	socklen_t addrlen;
	int bufsize = 1024;
	char *buffer = malloc(bufsize);
	struct sockaddr_in address, client_address;

	if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0)
	{
		printf("The socket is created\n");
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if (bind(create_socket, (struct sockaddr *)&address, sizeof(address)) == 0)
	{
		printf("Binding Socket\n");
	}

	while (1)
	{
		if (listen(create_socket, 10) < 0)
		{
			perror("Server: listen");
			exit(1);
		}

		if ((new_socket = accept(create_socket, NULL, NULL)) == -1)
		{
			perror("Server: accept");
			exit(1);
		}

		if (CONNECTION < 10)
		{
			CONNECTION++;
			printf("The Client %d is connected... \n", CONNECTION);
		recv(new_socket, buffer, bufsize, 0);
	    //printf("%s",buffer);
		process_request(buffer, new_socket);
		}

	}

	close(create_socket);
	return 0;
}
void process_request(char *rq, int fd)
{
	char *reqline[3], path[99999];
	reqline[0] = strtok(rq, " ");

	//If there is GET request
	if (strncmp(reqline[0], "GET\0", 4) == 0)
	{
		reqline[1] = strtok(NULL, " ");
		reqline[2] = strtok(NULL, "\r\n");

		//If request is not from HTTP/1.0 or HTTP/1.1
		if (strncmp(reqline[2], "HTTP/1.0\0", 9) != 0 && strncmp(reqline[2], "HTTP/1.1\0", 9) != 0)
		{
			write(fd, "HTTP/1.0 400 Bad Request\n", 25);
		}
		//If request is from required verson of HTTP
		else
		{
			int empty = 0;
			if (strncmp(reqline[1], "/\0", 2) == 0)
			{
				printf("No argument in HTTP request\n");
				//If no file is specified, index.html will be opened by default like it happens in APACHE...
				reqline[1] = "index.html";
				empty = 1;
			}

			//removing / from start
			char *name = reqline[1];
			if (empty == 0)
			{
				memmove(name, name + 1, strlen(name + 1) + 1);
			}

			struct stat buff;
			stat(name, &buff);

			if (S_ISREG(buff.st_mode) && (strncmp(get_filename_ext(name), "cgi", 3)) != 0)
			{
				do_cat(name, fd);
			}
			else if (S_ISDIR(buff.st_mode))
			{
				do_ls(name, fd);
			}
			else if (ends_in_cgi(name))
			{
				do_exec(name, fd);
			}
			else
			{
				do_404(fd);
			}
		}
	}
	//If request is not of GET
	else
	{
		cannot_do(fd);
	}

	//Closing SOCKET
	/*WRITE CODE  HERE*/

	CONNECTION--;
	return;
}

void cannot_do(int sock_fd)
{
	/*WRITE CODE  HERE*/
	/*Print this message in the same format(having three lines in total including an empty line) on client side:	         
		Content-type: text/plain
	        
	        That command is to be implementd
	*/
	write(sock_fd, "Content-Type: text/plain;\n\n",50);
	write(sock_fd, "HTTP/1.1 404 Not Found\r\n",50);
	write(sock_fd,"That command is to be implemented",25);

}

void do_cat(char *file_name, int fd)
{
	char data_to_send[BYTES];
	int fd2, bytes_read;
	printf("Doing Cat %s\n", file_name);

	write(fd, "HTTP/1.1 200 OK\n", 16);

	char *extension = get_filename_ext(file_name);

	if (strcmp(extension, "html") == 0)
	write(fd, "Content-Type: text/html\n\n", 25);
	else if (strcmp(extension, "gif") == 0)
		write(fd, "Content-Type: image/gif\n\n", 25);
	else if (strcmp(extension, "jpg") == 0)
		write(fd, "Content-Type: image/jpg\n\n", 25);
	else if (strcmp(extension, "jpeg") == 0)
		write(fd, "Content-Type: image/jpeg\n\n", 26);
	else
		write(fd, "Content-Type: text/plain\n\n", 26);

	//FILE FOUND
	if ((fd2 = open(file_name, O_RDONLY)) != -1)
	{
		int length;
		printf("Reading\n");
		if ((length = get_file_size(fd2)) == -1)
			printf("Error in getting size !\n");
		
		/*//sendfile(fd,fd2,0,2048);
		size_t total_bytes_sent = 0;
		ssize_t bytes_sent;
		while (total_bytes_sent < length)
		{
			//Zero copy optimization, moving data in kernal space
			if ((bytes_sent = sendfile(fd, fd2, 0, length - total_bytes_sent)) <= 0)
			{
				if (errno == EINTR || errno == EAGAIN)
				{
					continue;
				}
				perror("sendfile");
				
			}
			total_bytes_sent += bytes_sent;
		}*/
		int rv = 0;
		char buff[BYTES];
		while (rv = read(fd2, buff, BYTES)) {
			write(fd, buff, rv);
		}
	}
	else
	{
		printf("Not found\n");
		do_404(fd);
	}
	return;
}

void do_ls(char *dir_name, int fd)
{

	printf("Doing ls %s\n", dir_name);
	int cpid, status;
	cpid = fork();
	if (cpid == 0)
	{

		dup2(fd, 1);

		write(fd, "HTTP/1.1 200 OK\n", 16);
		write(fd, "Content-Type: text/plain\n\n", 26);
		DIR *dp = opendir(dir_name);
		errno = 0;
		struct dirent *entry;
		if (dp == NULL)
		{
			fprintf(stderr, "Can't open directory: %s", dir_name);
			exit(errno);
		}
		write(fd, strcat("Parent: ", dir_name), strlen(dir_name));
		while (1)
		{
			entry = readdir(dp);
			if (entry != NULL && errno != 0)
			{
				perror("readdir failed");
				exit(errno);
			}
			if (entry == NULL && errno == 0)
			{
				return;
			}
			else
			{
				//checck for hidden items
				if (entry->d_name[0] == '.')
					continue;
				write(fd, strcat("    ", entry->d_name), strlen(entry->d_name));
			}
		}
		closedir(dp);
	}
	else
	{
		wait(NULL);
	}
	return;
}

void do_404(int fd)
{
	/*WRITE CODE  HERE*/
	/*Write this message in the same format(having three lines in total) on client side:	         
		HTTP/1.0 404 Not Found
	        Content-Type: text/plain
	        Requested item not found
	*/
	write(fd, "Content-Type: text/html;\n\n",50);
	write(fd, "HTTP/1.1 404 Not Found\r\n",50);
	write(fd, "Server : Web Server in c\r\n\r\n",50);
	write(fd, "<html><head><title>404 Not Found</head></title>",50);
	write(fd, "<body><p>404 Not Found: The requested resource could not be found!</p></body></html>",70);
}

char *get_filename_ext(const char *filename)
{
	char *dot = strrchr(filename, '.');
	if (!dot || dot == filename)
		return "";
	return dot + 1;
}

int ends_in_cgi(char *name)
{
	/*WRITE CODE  HERE checking file extension*/
	if(strcmp(get_filename_ext(name),"cgi")==0)
	{
		return 1;
	}
	else return -1;
}

void do_exec(char *comm, int sock_fd)
{

	printf("Doing exec %s\n", comm);
	int cpid, status;
	dup2(sock_fd,1);
	cpid = fork();
	if (cpid == 0)
	{
		/*WRITE CODE  HERE*/
		/*Write this message in the same format(having one lines in total) on client side:	         
			HTTP/1.1 200 OK
	        Including other computations and functionality.
			execl("/usr/bin/php-cgi", "php-cgi", NULL);
	*/
    write(sock_fd, "Content-Type: text/html;\n\n",50);
	write(sock_fd, "HTTP/1.1 200 OK\r\n",50);
 	execl(comm, comm, NULL);
	}
	else
	{
		wait(NULL);
	}
	return;
}
void do_html(char *file_name,int fd)
{
  do_cat(file_name,fd); 
}