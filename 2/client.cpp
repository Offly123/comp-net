#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <chrono>
#include <string>

using namespace std;
using namespace chrono;

int createRequest()
{
  ofstream request("request.txt", ios::app);
  if (!request.is_open())
  {
    cout << "File not opened" << endl;
    return -1;
  }
  string name;
  
  cout << "Input student's name: ";
  cin >> name;
  request << name << "\t";
  
  cout << "Input 4 grades: ";
  for (int i = 0; i < 4; i++)
  {
    int grade;
    cin >> grade;
    request << grade << "\t";
  }
  request << endl;
  request.close();
  return 0;
}

void getAnswer()
{
  ifstream answer("answer.txt");

  int debt;
  answer >> debt;
  int min;
  answer >> min;
  answer.close();

  cout << "Debt: " << debt << endl;
  cout << "Min: " << min << endl;

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

int main() {
  const char* lastFilename = "answer.txt";
  struct stat lastFileStat;
  time_t lastModify = 0;
  if (stat(lastFilename, &lastFileStat) == 0)
  {
    lastModify = lastFileStat.st_mtime;
  }

  createRequest();

  cout << "Waiting for answer..." << endl;
  auto startOfWaiting = steady_clock::now();
  while (1)
  {
    auto currentWaiting = steady_clock::now();
    auto waitingTime = duration_cast<seconds>\
      (currentWaiting - startOfWaiting);
    if (waitingTime > 1s)
    {
      cout << "Server doesn't respond, try again later\n";
      
      return 0;
    }

    const char* newFilename = "answer.txt";
    struct stat newFileStat;
    time_t newModify = 0;
    if (stat(newFilename, &newFileStat) == 0 && newFileStat.st_size)
    {
      newModify = newFileStat.st_mtime;
    }
    
    if (lastModify != newModify)
      break;
  }

  getAnswer();

  return 0;
}