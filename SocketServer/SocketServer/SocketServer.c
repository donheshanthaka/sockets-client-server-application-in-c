/*
	C implenetation of a simple server client application that handles a single client using windows sockets API
	This file contains the server side code
*/

#include <stdio.h>
//#include <winsock.h>
#include <stdlib.h>
#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define PORT 19999

int main(){

	// Initiate the socket environment
	WSADATA w;
	int nReturn = 0;

	struct sockaddr_in srv; // make sure to have strcut in front when initializing sockaddr_in

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
	srv.sin_addr.s_addr = INADDR_ANY;
	srv.sin_port = htons(PORT);
	memset(&(srv.sin_zero), 0, 8);

	// binding the socket
	nReturn = bind(nSocket, (struct sockaddr*)&srv, sizeof(srv));
	if (nReturn < 0) {
		printf("Binding failed at port: %d\n", errno);
		return -1;
	}

	// listening for incoming connection 
	nReturn = listen(nSocket, 1);
	if (nReturn < 0) {
		printf("Listening failed at port: %d\n", errno);
		return -1;
	}

	// through the listner socket, listening for incoming connection and once found communication will be maintained in a new socket
	int nClient = 0;
	int addrelen = sizeof(srv);
	nClient = accept(nSocket, (struct sockaddr*)&srv, &addrelen);
	if (nClient < 0) {
		printf("Accepting client failed: %d\n", errno);
		return -1;
	}

	char sBuff[1024] = {0,};

	while (1) {
		memset(sBuff, 0, 1024);
		nReturn = recv(nClient, sBuff, 1024, 0);
		if (nClient < 0) {
			printf("Recieving message failed at port: %d\n", errno);
			return -1;
		}
		printf("Message recievd from client: %s\n", sBuff);
	}

	return 0;
}