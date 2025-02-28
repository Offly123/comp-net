#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <string>

using namespace std;
using namespace this_thread;
using namespace chrono;

void changePointerfile(int pointer)
{
  ofstream pointerfile("pointer.txt");
  pointerfile << pointer << endl;
  pointerfile.close();
}

void getRequest(int* grades, int& pointer)
{
  ifstream request("request.txt");
  request.seekg(pointer, ios::beg);
  string name;

  request >> name;
  cout << "grades: ";
  for (int i = 0; i < 4; i++) 
  {
    request >> grades[i];
    cout << grades[i] << " ";
  }
  cout << endl;
  pointer = request.tellg();
  changePointerfile(pointer);
  request.close();
}

void createAnswer(int mas[], int& pointer)
{
  int debt = 0;
  double min = 5;
  for (int i = 0; i < 4; i++)
  {
    debt += (mas[i] < 3);
    if (min > mas[i])
      min = mas[i];
  }
  ofstream answer("answer.txt");
  cout << "debt: " << debt << endl;
  cout << "min: " << min << endl;
  answer << debt << "\t" << min << endl;

  answer.close();
}

int main() {
  ifstream pointerfile("pointer.txt");
  int pointer = 0;
  if (!pointerfile.is_open())
  {
    cout << "Couldn't find pointer.txt, may cause errors\n";
  } else
  {
    pointerfile >> pointer;
  }
  pointerfile.close();
  const char* lastFilename = "request.txt";
  struct stat lastFileStat;
  int lastSize;
  if (stat(lastFilename, &lastFileStat) != 0)
  {
    lastSize = 0;
  }

  lastSize = lastFileStat.st_size;
  int grades[4];

  while (1)
  {
    sleep_for(chrono::milliseconds(500));

    const char* newFilename = "request.txt";
    struct stat newFileStat;

    if (stat(newFilename, &newFileStat) != 0) 
    {
      pointer = 0;
      changePointerfile(pointer);
      continue;
    }

    int newSize = newFileStat.st_size;

    if ((lastSize != newSize) && newSize != 0)
    {
      cout << "Creating answer...\n";
      getRequest(grades, pointer);
      createAnswer(grades, pointer);
      lastSize = newSize;
    }
    lastSize = newSize;
  }
  return 0;
}