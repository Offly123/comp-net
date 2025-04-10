#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")

void showError();
void showError(SOCKET);



// Вывести ошибку, закрыть сокет, если он передан
void showError() {
	std::cout << "Error: " << WSAGetLastError() << "\n";
	WSACleanup();
}
void showError(SOCKET sock) {
	std::cout << "Error: " << WSAGetLastError() << "\n";
	closesocket(sock);
	WSACleanup();
}
void showError(SOCKET sock1, SOCKET sock2) {
	std::cout << "Error: " << WSAGetLastError() << "\n";
	closesocket(sock1);
	closesocket(sock2);
	WSACleanup();
}