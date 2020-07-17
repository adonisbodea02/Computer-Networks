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

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);
	
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in client;
	
	client.sin_family = AF_INET;
	client.sin_port = htons(9999);
	server.sin_addr.s_addr = inet_addr("192.168.0.35");
	
	int c = connect(s, (struct sockaddr)* &client, sizeof(client));
	
	char message[100];
	char s[10] = "Smaller\0";
	char l[10] = "Larger\0";
	int ok = 1;
	srand(time(NULL));
	int random = rand() % 10;
	int old_random = random;
	
	while(ok){
		
		memset(message, 0);
		printf("My random number this time is: %d\n", random);
		send(s, &random, sizeof(int), 0);
		
		recv(s, message, sizeof(message), 0);
		printf("I received: %s", message);
		
		if(strcmp(s, message) == 0){
			random = rand()% random;
		}
		else
		{
			if(strcmp(l, message) == 0)
			{
				random = random + rand()%(10-random);
			}
			else
			{
				printf("%s", message);
				ok = 0;
			}
		}
	}
	
	closesocket(s);
	WSACleanup();
	system("pause");
	return 0;
}
