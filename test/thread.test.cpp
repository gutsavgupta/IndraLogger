#include "Clogger.h"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using Severity = typename clogger::Clogger::SeverityT;
std::string line;

void LogThread()
{
    while (std::getline(std::cin, line))
    {
        CLOG(Severity::DEBUG, "input[" << line << "]");
    }
    return;
}

void DumpThread()
{
    // auto lastTime      = std::chrono::system_clock::now();
    // auto durationInSec = std::chrono::seconds(10);
    // while (0)
    // {
    //     auto time = std::chrono::system_clock::now();
    //     if (time > lastTime + durationInSec)
    //     {
    //         std::cout << "hello world" << std::endl;
    //         lastTime = time;
    //     }
    // }
    clogger::Clogger::GetInstance().Run();
    return;
}

int main()
{
    std::thread logThread(LogThread);
    std::thread dumpThread(DumpThread);

    logThread.join();
    dumpThread.join();

    return 0;
}
