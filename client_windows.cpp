#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

using namespace std;

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);
	
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	
	sockaddr_in client_addr;
	
	//char question[] = "Which is the only team that have won the Golden EPL?\0";
	
	client_addr.sin_addr.s_addr = inet_addr("192.168.0.35");
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(9999);
	
	int c = connect(s, (SOCKADDR*) &client_addr, sizeof(client_addr));
	
	if (c < 0)
	{
		printf("Can't connect to socket\n");
		system("pause");
		exit(1);
	}
	
	char question[1200];
	char answer[50];
	char result[50];
	memset(question, 0, 50); 
	memset(answer, 0, 50);
	memset(result, 0, 50);
	
	recv(s, question, sizeof(question), 0);
	printf("Question: %s\n", question);
	
	printf("Your answer: ");
	scanf("%s", answer);
	answer[strlen(answer)] = '\0';
	send(s, answer, sizeof(answer), 0);
	
	c = recv(s, result, sizeof(result), 0);
	printf("Result: %s\n", result);
	
	closesocket(s);
	WSACleanup();
	system("pause");
	return 0;
}