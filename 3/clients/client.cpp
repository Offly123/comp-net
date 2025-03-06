#include <sys/stat.h>
#include <unistd.h>
#include <chrono>
#include <string>
#include "../includes/handler.h"

using namespace chrono;

int main() {
    cout << "Client started\n";

    const char* lastFileName = "answer.txt";
    struct stat lastFileStat;
    time_t lastModified = 0;
    if (stat(lastFileName, &lastFileStat) == 0) {
        lastModified = lastFileStat.st_mtime;
    }


    requestStruct request;
    request.create();


    request.write();


    cout << "Waiting for answer...\n\n";
    auto startOfWaiting = steady_clock::now();
    while (true) {
        auto currentWaiting = steady_clock::now();
        auto waitingTime = duration_cast<seconds>(
            currentWaiting - startOfWaiting
        );
        if (waitingTime > 1s) {
            cout << "Server doesn't respond, try again later\n";
            int a;
            cin >> a;
            return 0;
        }

        const char* newFileName = "answer.txt";
        struct stat newFileStat;
        time_t newModified = 0;
        if (stat(newFileName, &newFileStat) == 0) {
            newModified = newFileStat.st_mtime;
        }
        
        if (lastModified != newModified && newFileStat.st_size) {
            break;
        }
    }

    answerStruct answer;
    answer.read();

    int a;
    cin >> a;
    return 0;
}