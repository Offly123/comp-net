#include <sys/stat.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <string>
#include "handle_request.h"

using namespace this_thread;
using namespace chrono;

void changePointerfile(int pointer)
{
  ofstream pointerfile("pointer.txt");
  pointerfile << pointer << endl;
  pointerfile.close();
}

int main() {
  ifstream pointerfile("pointer.txt");
  int pointer = 0;
  if (!pointerfile.is_open())
  {
    cout << "Couldn't find pointer.txt, may cause errors\n";
  } else {
    pointerfile >> pointer;
  }
  pointerfile.close();
  const char* lastFilename = "request.txt";
  struct stat lastFileStat;
  time_t lastModified;
  if (stat(lastFilename, &lastFileStat) != 0)
  {
    lastModified = 0;
  }

  lastModified = lastFileStat.st_mtime;
  int grades[4];

  while (true)
  {
    sleep_for(milliseconds(500));

    const char* newFilename = "request.txt";
    struct stat newFileStat;

    if (stat(newFilename, &newFileStat) != 0)
    {
      pointer = 0;
      changePointerfile(pointer);
      continue;
    }

    time_t newModified = newFileStat.st_mtime;
    
    if ((lastModified != newModified) && newModified != 0)
    {
      requestStruct request;
      request.read();
      answerStruct answer;
      answer.create(request.grades);
      answer.send();

      lastModified = newModified;
    }
    lastModified = newModified;
  }
  return 0;
}