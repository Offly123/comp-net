#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MAX_MESSAGE_SIZE 255

#include <iostream>
#include <WinSock2.h>
#include <string>

#pragma comment (lib, "Ws2_32.lib")

using namespace std;


// Вывести ошибку, закрыть сокет если передан
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
	while (buf[i] != '\0' && i <= MAX_MESSAGE_SIZE) {
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


	SOCKET clientSocket;
	if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		showError(clientSocket);
		return -1;
	}


	sockaddr_in clientAddr;
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(8080);
	clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if ( connect(clientSocket, (sockaddr*)&clientAddr, sizeof(clientAddr)) == SOCKET_ERROR) {
		showError(clientSocket);
		return -1;
	}


	cout << "Connected to server\n";



	string clientMessage;
	string serverMessage;
	while (serverMessage != "Goodbye") {
		getline(cin, clientMessage);
		char* buf = stringToChar(clientMessage);
		send(clientSocket, buf, MAX_MESSAGE_SIZE, 0);
		if (clientMessage == "Goodbye") {
			break;
		}

		buf = new char[MAX_MESSAGE_SIZE];
		recv(clientSocket, buf, MAX_MESSAGE_SIZE, 0);
		serverMessage = charToString(buf);
		cout << "Server message: " << serverMessage << "\n";
	}

	
	closesocket(clientSocket);
	WSACleanup();
	return 0;
}