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



	// Создание IpV4 TCP/IP сокет
	SOCKET serverSocket;
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		showError(serverSocket);
		return -1;
	}



	// Настройка IP и порта
	sockaddr_in serverAddr;

	string IP;
	cout << "Input IP: ";
	cin >> IP;

	int port;
	cout << "Input port: ";
	cin >> port;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(IP.c_str());
	serverAddr.sin_port = htons(port);

	if ( connect(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		showError(serverSocket);
		return -1;
	}



	cout << "Connected to server\n";


	
	request req;
	req.createRequest();
	cout << "here hehe\n";
	req.sendRequest(serverSocket);

	response res;
	res.getResponse(serverSocket);



	cout << "Scholarship: " << res.message << "\n";
	cout << "Debt count: " << res.debtSize << "\n";	


	
	closesocket(serverSocket);
	WSACleanup();
	return 0;
}