// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// author A.C. Gadiatulin group CPLUS-1006 block-3 Linux client-server app
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <iomanip>
#include "User.h"
#include "Utilites.h"
#include "Message.h"
#include "MyContainers.h"
#include "HandleGeneral.h"

#pragma warning(disable: 4996)

/**
*		g++ -o client client.cpp -lws2_32
*/

void clientHandler() {
	// receive message from server
	char msg[256];
	char msg2[256];
	while(true) {
		recv(connection, msg, sizeof(msg), 0);		// pass message
		recv(connection, msg2, sizeof(msg), 0);		// pass login
		allContainers.insert(std::make_pair(msg2, msg));
	}
}

int main(int argc, char* argv[]) {
	setlocale(0, "");
	
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if(WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(50000);
	addr.sin_family = AF_INET;

	connection = socket(AF_INET, SOCK_STREAM, 0);
	if(connect(connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	std::cout << "Client start working and connected!\n";

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)clientHandler, 0, 0, 0);
						
	bool isExit{true};
	char buffer[256];
	while(isExit) {
		callHandleFunction(isExit);
		std::cout << "send to server for client or type to exit <:exit>: \t";
		int s = scanf("%s", &buffer[0]);
		send(connection, buffer, sizeof(buffer), 0);
		if (strcmp(buffer, ":exit") == 0) {			
			std::cout << "\nDisconnected from server.\n";
			exit(1);
		}
		Sleep(10);
	}
	system("pause");
	return 0;
}

