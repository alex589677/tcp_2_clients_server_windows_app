// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// author A.C. Gadiatulin group CPLUS-1006 block-3 Linux client-server app
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <cstring>
#include <map>

#pragma warning(disable: 4996)

using namespace std;

SOCKET connections[100];	// box clients
int counter = 0;		// index connections

/**
*		g++ -o server server.cpp -lws2_32
*/

void ClientHandler(int index) {
	char msg[256];
	while(true) {
		// receive messega on clients
		recv(connections[index], msg, sizeof(msg), 0);
		if (strcmp(msg, ":exit") == 0) {
			counter--;
			std::cout << " one client disconnecting.\n";
			break;
		}
		std::cout << "> " << "connecting!\n";
		
		// send message another client
		for(int i = 0; i < counter; i++) {
			if(i == index) {
				continue;
			}
			send(connections[i], msg, sizeof(msg), 0);
		}
	}
}

int main(int argc, char* argv[]) {
	setlocale(0, "");
	
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if(WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Error" << endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(50000);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	std::cout << "Server start working...\n";
	for(size_t i = 0; i < 2; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
		if(newConnection == 0) {
			cout << "Error #2\n";
		} else {
			cout << "Client Connected!\n";
			connections[i] = newConnection;		
			counter++;
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ClientHandler, reinterpret_cast<LPVOID>(i), 0, 0);	// (LPVOID)
		}
	}
	system("pause");
	return 0;
}