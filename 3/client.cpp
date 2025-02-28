#include <sys/stat.h>
#include <unistd.h>
#include <chrono>
#include <string>
#include "handle_request.h"

using namespace chrono;
// Доделать это когда-нибудь.
// Должно выдавать все запросы, но для 
// этого надо хранить длину в начале 
// и ещё и строки записывать, гадем короче.
// Время 18:38 так впадлу. Пойду кушать
void getAllRequests()
{
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

int main() {
  const char* lastFileName = "answer.txt";
  struct stat lastFileStat;
  time_t lastModified = 0;
  if (stat(lastFileName, &lastFileStat) == 0)
  {
    lastModified = lastFileStat.st_mtime;
  }


  requestStruct request;
  request.create();
  if (request.name == "Admin")
  {
    
    getAllRequests();
    return 0;
  }
  request.send();


  cout << "Waiting for answer..." << endl;
  auto startOfWaiting = steady_clock::now();
  while (true)
  {
    auto currentWaiting = steady_clock::now();
    auto waitingTime = duration_cast<seconds>(
        currentWaiting - startOfWaiting
        );
    if (waitingTime > 1s)
    {
      cout << "Server doesn't respond, try again later\n";
      return 0;
    }

    const char* newFileName = "answer.txt";
    struct stat newFileStat;
    time_t newModified = 0;
    if (stat(newFileName, &newFileStat) == 0)
    {
      newModified = newFileStat.st_mtime;
    }
    
    if (lastModified != newModified && newFileStat.st_size)
      break;
  }

  answerStruct answer;
  answer.read();

  return 0;
}