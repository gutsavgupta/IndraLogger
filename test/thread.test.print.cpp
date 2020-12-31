#include <QLogger.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using Severity = typename qlogger::QLogger::SeverityT;
std::string line;

void LogThread()
{
    uint64_t avgTime = 0;
    uint64_t count   = 0;
    auto&    logger  = qlogger::QLogger::GetInstance().GetLogger();
    while (std::getline(std::cin, line))
    {
        auto time1 = std::chrono::high_resolution_clock::now();
        LOG(logger, Severity::DEBUG, " " << line);
        // CLOG(Severity::DEBUG, "input[" << line << "]");

        auto time2 = std::chrono::high_resolution_clock::now();
        auto time3 = std::chrono::high_resolution_clock::now();

        auto timeDiff =
          std::chrono::duration_cast<std::chrono::nanoseconds>(time2 - time1);
        auto clockDiff =
          std::chrono::duration_cast<std::chrono::nanoseconds>(time3 - time2);

        avgTime += timeDiff.count();
        ++count;

#if 0
        std::cout << "time for logging a message of len:" << line.length()
                  << " is ns:" << timeDiff.count()
                  << " and time for clock::now() ns:" << clockDiff.count()
                  << " avgTime:" << (1.0 * avgTime) / count << std::endl;
#endif
    }
    return;
}

void DumpThread()
{
    auto lastTime      = std::chrono::system_clock::now();
    auto durationInSec = std::chrono::seconds(10);
    while (1)
    {
        auto time = std::chrono::system_clock::now();
        if (1 or time > lastTime + durationInSec)
        {
            qlogger::QLogger::GetInstance().Run();
            lastTime = time;
        }
    }
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
