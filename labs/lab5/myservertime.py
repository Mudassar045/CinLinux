import datetime;
import socket;
sockfd=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sockfd.bind(('0.0.0.0',54154))
print(datetime.datetime.now())
while True:
	payload, client_addr=sockfd.recvfrom(1024)
	sockfd.sendto(datetime.datetime.now().strftime("%d/%m/%y"), client_addr)
