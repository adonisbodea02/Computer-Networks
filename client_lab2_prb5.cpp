#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

using namespace std;

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);
	
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
	
	if(s < 0){
		printf("Error creating socket!\n");
		return 1;
	}
	
	struct sockaddr_in client;
	struct sockaddr_in server;
	uint32_t message;
	int* len = 0;
	
	
	if(argc != 2)
	{
		printf("I did not received a domain to send to server\n");
		return 1;
	}
	
	memset(&server, 0, sizeof(client));
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);
	server.sin_addr.s_addr = inet_addr("192.168.0.35");
	printf("%d\n", strlen(argv[1]));
	
	int n = sendto(s, argv[1], strlen(argv[1]), 0, (struct sockaddr*) &server, sizeof(sockaddr));
	
	if(n < 0)
	{
		printf("Error at function sendto\n");
		return 1;
	}
	
	recvfrom(s, (char*)&message, 4, 0, (struct sockaddr*) &server, len);
	
	uint32_t new_message;
	new_message = ntohl(message);
	
	printf("I received %d %d\n", new_message, message);

	closesocket(s);
	WSACleanup();
	system("pause");
	return 0;
}
	
	
	
	
	
	
	
	
	
	