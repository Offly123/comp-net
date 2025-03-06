#include <iostream>
#include <fstream>

using namespace std;

struct requestStruct {
  int grades[4];
  int length;
  string name;

  void create()
  {
    cout << "Input student's name: ";
    cin >> name;
    if (name == "Admin")
      return;
    cout << "Input 4 grades: ";
    for (int i = 0; i < 4; i++)
    {
      cin >> grades[i];
    }
    cout << "Request created\n";
  }

  void send()
  {
    ofstream request("request.txt", ios::binary | ios::app);
    request.write((char* )this, sizeof(int)*5);
    request.close();
    cout << "Request sent\n";
  }

  void read()
  {
    int pointer = 0;
    ifstream pointerGet("pointer.txt");
    if (!pointerGet.is_open())
    {
      cout << "pointer.txt doesn't found, may cause errors\n";
    } else { 
      pointerGet >> pointer;
    }
    pointerGet.close();
    ifstream answer("request.txt", ios::binary);
    answer.seekg(pointer);
    answer.read((char* )this, sizeof(int)*5);
    pointer = answer.tellg();
    ofstream pointerSet("pointer.txt");
    pointerSet << pointer;
    pointerSet.close();
    cout << "Request received\n";
    answer.close();
  }
};

struct answerStruct {
  int min;
  int debt;

  void create(int* grades)
  {
    debt = 0;
    min = 5;
    for (int i = 0; i < 4; i++)
    {
      debt += (grades[i] < 3);
      if (min > grades[i])
        min = grades[i];
    }
    cout << "Answer created\n";
  }

  void send()
  {
    ofstream answer("answer.txt", ios::binary);
    answer.write((char* )&min, sizeof(answerStruct));
    answer.close();
    cout << "Answer sent\n";
  }

  void read()
  {
    ifstream answer("answer.txt", ios::binary);

    answer.read((char* )this, sizeof(answerStruct));

    cout << "Debt: " << debt << endl;

    if (min < 4)
    {
      cout << "No scholarship" << endl;
      return;
    }
    if (min < 5)
    {
      cout << "Base scholarship" << endl;
      return;
    }
    cout << "Elevated scholarship" << endl;
    return;
  }
};