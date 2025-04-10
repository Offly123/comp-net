#include <request_response.h>

using namespace std;



int main() {
	setlocale(LC_ALL, "ru");



	// Подключение сокетов
	WSAData ws;
	if (WSAStartup(MAKEWORD(2, 2), &ws)) {
		showError();
		return -1;
	}



	// Создание IpV4 TCP/IP сокета
	SOCKET serverSocket;
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		showError(serverSocket);
		return -1;
	}



	// Настройка IP и порта
	sockaddr_in serverAddr;

	//string IP;
	//cout << "Input IP: ";
	//getline(cin, IP);

	//int port;
	//cout << "Input port: ";
	//cin >> port;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("192.168.1.123");
	serverAddr.sin_port = htons(123);

	// Подключаем сокет и начинаем слушать
	if ( bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) ) {
		showError(serverSocket);
		return -1;
	}
	if (listen(serverSocket, SOMAXCONN) ) {
		showError(serverSocket);
		return -1;
	}


	while (1) {

		// Принимаем соединение и создаём сокет клиента
		cout << "Waiting for connections...\n";
		int socketAddrSize = sizeof(serverAddr);
		SOCKET clientSocket = accept(serverSocket, (sockaddr*)&serverAddr, &socketAddrSize);
		if (clientSocket == INVALID_SOCKET) {
			closesocket(clientSocket);
			cout << "Bad socket\n";
			continue;
		}



		cout << "Client connected\n";



		request req;
		req.getRequest(clientSocket);

		response res;
		res.createResponse(req);
		using std::cout, std::cin;
		cout << "Debt: " << res.debtSize;
		cout << "\nSho: " << res.message << "\n";
		res.sendResponse(clientSocket);



		closesocket(clientSocket);
	}


	closesocket(serverSocket);
	WSACleanup();
	return 0;
}