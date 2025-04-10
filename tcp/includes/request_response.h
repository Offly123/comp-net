#pragma once

#define MAX_REQUEST_SIZE 4096
#define MAX_RESPONSE_SIZE 4096
#define GRADE_COUNT 4
#define MAX_NAME_SIZE 128
#define MAX_MESSAGE_SIZE 128

#include <winsockError.h>
#include <string>

struct request {
	int grades[GRADE_COUNT];
	char name[MAX_NAME_SIZE];


	void createRequest() {
		std::cout << "Something\n";
		std::cin >> name;
		std::cout << "Something2\n";
		for (int i = 0; i < GRADE_COUNT; i++) {
			std::cin >> grades[i];
		}
	}


	void sendRequest(SOCKET& serverSocket) {
		send(serverSocket, (char*)this, MAX_REQUEST_SIZE, 0);
	}

	void getRequest(SOCKET& clientSocket) {
		std::cout << "before recv\n";
		recv(clientSocket, (char*)this, MAX_REQUEST_SIZE, 0);
		std::cout << "after recv\n";
		std::cout << "Request received\nName: " << name << "\nGrades: ";

		for (int i = 0; i < GRADE_COUNT; i++) {
			std::cout << grades[i] << " ";
		}
		std::cout << "\n\n";
	}
};

struct response {
	char message[MAX_MESSAGE_SIZE];
	int debtSize = 0;

	void createResponse(request req) {

		int min = req.grades[0];
		for (int i = 0; i < GRADE_COUNT; i++) {
			debtSize += req.grades[i] < 3;
			if (req.grades[i] < min) {
				min = req.grades[i];
			}
		}

		if (min == 5) {
			strcpy_s(message, "Elevated scholarship");
			return;
		}
		if (min == 4) {
			strcpy_s(message, "Normal scholarship");
			return;
		}
		strcpy_s(message, "No scholarship");
	}

	void sendResponse(SOCKET& clientSocket) {
		send(clientSocket, (char*)this, MAX_RESPONSE_SIZE, 0);
	}

	void getResponse(SOCKET& serverSocket) {
		recv(serverSocket, (char*)this, MAX_RESPONSE_SIZE, 0);
	}
};