#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MAX_MESSAGE_SIZE 255

#include <iostream>
#include <WinSock2.h>
#include <string>

#pragma comment (lib, "Ws2_32.lib")

using namespace std;


// Вывести ошибку, закрыть сокет, если он передан
void showError() {
	cout << "Error: " << WSAGetLastError() << "\n";
	WSACleanup();
}

void showError(SOCKET sock) {
	cout << "Error: " << WSAGetLastError() << "\n";
	closesocket(sock);
	WSACleanup();
}


// Преобразует string в char* и ставит в конец '\0'
char* stringToChar(string str) {
	char* buf = new char[MAX_MESSAGE_SIZE];

	for (int i = 0; i < str.size(); i++) {
		buf[i] = str[i];
	}
	buf[str.size()] = '\0';

	return buf;
}

string charToString(char* buf) {
	string str = "";

	int i = 0;
	while (buf[i] != '\0' && i <= 255) {
		str += buf[i++];
	}

	return str;
}



int main() {
	WSAData ws;
	if (WSAStartup(MAKEWORD(1, 1), &ws)) {
		showError();
		return -1;
	}


	SOCKET serverSocket;
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		showError(serverSocket);
		return -1;
	}


	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8080);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
	listen(serverSocket, SOMAXCONN);

	int socketAddrSize = sizeof(serverAddr);
	SOCKET clientSocket = accept(serverSocket, (sockaddr*)&serverAddr, &socketAddrSize);
	if (clientSocket == INVALID_SOCKET) {
		showError(serverSocket);
		return -1;
	}

	cout << "Client connected\n";



	string clientMessage;
	string serverMessage;
	while (serverMessage != "Goodbye") {
		char* buf = new char[MAX_MESSAGE_SIZE];
		recv(clientSocket, buf, MAX_MESSAGE_SIZE, 0);
		clientMessage = charToString(buf);
		cout << "Client message: " << clientMessage << "\n";

		if (clientMessage == "Goodbye") {
			break;
		}
		getline(cin, serverMessage);
		buf = stringToChar(serverMessage);
		send(clientSocket, buf, MAX_MESSAGE_SIZE, 0);
	}



	closesocket(serverSocket);
	closesocket(clientSocket);
	WSACleanup();
	return 0;
}