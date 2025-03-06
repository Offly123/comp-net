#include <sys/stat.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <string>
#include "../includes/handler.h"

using namespace this_thread;
using namespace chrono;

int main() {
    cout << "Server started\n";

    const char* lastFilename = "./requests/request.txt";
    struct stat lastFileStat;
    time_t lastModified;
    if (stat(lastFilename, &lastFileStat) != 0) {
        lastModified = 0;
    }

    lastModified = lastFileStat.st_mtime;
    int grades[4];

    while (true) {
        sleep_for(milliseconds(500));
        const char* newFilename = "./requests/request.txt";
        struct stat newFileStat;

        if (stat(newFilename, &newFileStat) != 0) {
            continue;
        }

        time_t newModified = newFileStat.st_mtime;
        
        if ((lastModified != newModified) && newModified != 0) {
            requestStruct request;
            request.read();
            answerStruct answer;
            answer.create(  
                request.grades,
                request.name, 
                request.pathToClient
            );
            answer.write();

            lastModified = newModified;
        }
        lastModified = newModified;
    }
    return 0;
}