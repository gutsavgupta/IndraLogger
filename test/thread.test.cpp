#include <QLogger.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using Severity = typename qlogger::QLogger::SeverityT;
std::string line;

void LogThread2()
{
    constexpr int MAX_ITR{ 20000 };
    auto&         logger   = qlogger::QLogger::GetInstance().GetLogger();
    auto          time1    = std::chrono::high_resolution_clock::now();
    auto          bechmark = "benchmark";
    for (auto _ = 0; _ < MAX_ITR; ++_)
    {
        LOG(logger, Severity::DEBUG, "input[" << bechmark << "]");
    }
    auto time2 = std::chrono::high_resolution_clock::now();
    auto timeDiff =
      std::chrono::duration_cast<std::chrono::nanoseconds>(time2 - time1);

    std::cout << "Average logging time:" << (1.0 * timeDiff.count()) / MAX_ITR
              << " ns" << std::endl;
    return;
}

void LogThread()
{
    uint64_t avgTime = 0;
    uint64_t count   = 0;
    auto&    logger  = qlogger::QLogger::GetInstance().GetLogger();
    while (std::getline(std::cin, line))
    {
        auto time1 = std::chrono::high_resolution_clock::now();
        LOG(logger, Severity::DEBUG, "input[" << line << "]");
        // CLOG(Severity::DEBUG, "input[" << line << "]");

        auto time2 = std::chrono::high_resolution_clock::now();
        auto time3 = std::chrono::high_resolution_clock::now();

        auto timeDiff =
          std::chrono::duration_cast<std::chrono::nanoseconds>(time2 - time1);
        auto clockDiff =
          std::chrono::duration_cast<std::chrono::nanoseconds>(time3 - time2);

        avgTime += timeDiff.count();
        ++count;

        std::cout << "time for logging a message of len:" << line.length()
                  << " is ns:" << timeDiff.count()
                  << " and time for clock::now() ns:" << clockDiff.count()
                  << " avgTime:" << (1.0 * avgTime) / count << std::endl;
    }
    return;
}

void DumpThread()
{
    // qlogger::QLogger::GetInstance().Run();
    return;
}

int main()
{
    std::thread logThread(LogThread2);
    std::thread dumpThread(DumpThread);

    logThread.join();
    dumpThread.join();
    return 0;
}
