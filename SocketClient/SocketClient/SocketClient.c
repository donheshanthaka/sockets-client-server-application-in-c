/*
	C implenetation of a simple server client application that handles a single client using windows sockets API
	This file contains the client side code
*/

#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define PORT 19999

int main() {

	// Initiate the socket environment
	WSADATA w;
	int nReturn = 0;

	struct sockaddr_in srv; // make sure to have strcut in front when initializing sockaddr_in

	// Initializing the library
	nReturn = WSAStartup(MAKEWORD(2, 2), &w);
	if (nReturn < 0) {
		printf("Initialization failed on socket library!\n");
		return -1;
	}

	// open a socket - listern socket that will listen on a port for incomming connections from the client
	int nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (nSocket < 0) {
		// errno is a system global variable which gets updated with the last API call return value
		printf("Initialization failed on listner socket: %d\n", errno);
		return -1;
	}

	srv.sin_family = AF_INET;
	//srv.sin_addr.s_addr = inet_addr("192.168.1.100");
	InetPton(AF_INET, (PCWSTR)("192.168.1.100"), &srv.sin_addr.s_addr);
	srv.sin_port = htons(PORT); // using htons to convert into network byte order
	memset(&(srv.sin_zero), 0, 8);

	nReturn = connect(nSocket, (struct sockaddr*) &srv, sizeof(srv));
	if (nReturn < 0) {
		printf("Connection to the server failed: %d\n", errno);
		return -1;
	}
	// if connected, keep sending messages
	char sBuff[1024] = { 0, };
	while (1) {
		Sleep(2000);
		printf("Enter the message: ");
		fgets(sBuff, 1023, stdin);
		send(nSocket, sBuff, strlen(sBuff), 0);
	}

	return 0;
}