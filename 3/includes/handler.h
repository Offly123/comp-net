#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

using namespace std;
using namespace filesystem;


// Строка в char* и наоборот
char* stringToChar(string);
string charToString(char*, int);


// Запись в файл
void writeInFile(ofstream&, string);
void writeInFile(ofstream&, int*, int);
void writeInFile(ofstream&, int);


// Чтение из файла
string readFromFileString(ifstream&);
int readFromFileInt(ifstream&);
int* readFromFileArray(ifstream&, int);


// Структура запроса
struct requestStruct {
	int* grades;
	string name;
	string pathToClient;


	// Получает имя и 4 оценки, записывает в поля структуры
	void create() {
		grades = new int[4];
		cout << "Input student's name: ";
		cin >> name;
		cout << "Input 4 grades: ";
		for (int i = 0; i < 4; i++) {
		cin >> grades[i];
		}
		cout << "\nRequest created\n";
	}


	// Записывает поля структуры в файл
	//
	// TODO: сделать так, чтобы сервер выдавал клиентам UID
	// при первой отправке запроса.
	//
	// Сервер должен читать список файлов в папке с запросами и
	// проверять есть ли новые запросы. Возможно удалять запрос
	// при успешном чтении
	void write() {
		ofstream request(
			"/home/offly/Desktop/comp-net/3/server/requests/request.txt", 
			ios::binary
		);


		writeInFile(request, current_path());
		writeInFile(request, name);
		writeInFile(request, grades, 4);
		delete[]grades;

		request.close();
		cout << "Request sent\n";
	}


	// Считывает запрос в поля структуры
	void read() {
		ifstream request(
			"./requests/request.txt", 
			ios::binary
		);


		pathToClient = readFromFileString(request);
		name         = readFromFileString(request);
		grades   	 = readFromFileArray(request, 4);


		cout << "Request received\n";

		request.close();
	}
};


// Структура ответа
struct answerStruct {
	int min;
	int debt;
	string name;
	string pathToClient;


	// Присваивает полям значения из запроса
	void create(int* grades, string name, string pathToClient) {
		this->name = name;
		this->pathToClient = pathToClient;
		debt = 0;
		min = 5;

		for (int i = 0; i < 4; i++) {
			debt += (grades[i] < 3);
			if (min > grades[i]) {
				min = grades[i];
			}
		}
		cout << "Answer created\n";
	}


	// Записывает поля в файл
	void write() {
		pathToClient += "/answer.txt";
		ofstream answer(pathToClient, ios::binary);


		writeInFile(answer, name);
		writeInFile(answer, min);
		writeInFile(answer, debt);


		answer.close();
		cout << "Answer sent\n\n";
	}


	// Читает ответ
	void read()
	{
		ifstream answer("answer.txt", ios::binary);

		int nameSize = -1;
		
		name = readFromFileString(answer);
		min  = readFromFileInt(answer);
		debt = readFromFileInt(answer);

		cout << "Student name: " << name << endl;
		cout << "Debt: " << debt << endl;

		if (min < 4) {
			cout << "No scholarship" << endl;
			return;
		}
		if (min < 5) {
			cout << "Base scholarship" << endl;
			return;
		}
		cout << "Elevated scholarship" << endl;
		return;
	}
};


char* stringToChar(string str) {
  	char* buf = new char[255];

    for (int i = 0; i < str.size(); i++) {
		buf[i] = str[i];
	}

	return buf;
}


string charToString(char* buf, int length) {
	string str;

	for (int i = 0; i < length; i++) {
		str += buf[i];
	}

	return str;
}


void writeInFile(ofstream &file, string str) {
	int size = str.size();
	file.write((char*)&size, sizeof(int));

	char* buf = stringToChar(str);
	file.write(buf, size);
}


void writeInFile(ofstream &file, int* mas, int n) {
	file.write((char*)mas, sizeof(int) * n);
}


void writeInFile(ofstream &file, int num) {
	file.write((char*)&num, sizeof(int));
}


string readFromFileString(ifstream &file) {
	int strSize;
	file.read((char*)&strSize, sizeof(int));

	char* buf = new char[255];
	file.read(buf, strSize);

	string str = charToString(buf, strSize);

	delete[]buf;
	return str;
}


int readFromFileInt(ifstream &file) {
	int num;

	file.read((char*)&num, sizeof(int));

	return num;
}


int* readFromFileArray(ifstream &file, int n) {
	int* num = new int[4];

	file.read((char*)num, sizeof(int) * n);

	return num;
}