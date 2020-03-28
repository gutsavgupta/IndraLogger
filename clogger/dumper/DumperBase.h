/*
 * Basic Dumper to dump the logs
 * virtual functions allowed
 */

#pragma once

#include <cstdint>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace clogger {
namespace dumper {

template <typename BufferType, typename DumperType>
struct NoCopyReader
{
    using DumperT = DumperType;
    using BufferT = BufferType;

    explicit NoCopyReader(DumperT& dumper)
      : m_dumper(dumper)
      , m_priority(0)
    {
    }

    bool ReadPriority(BufferT& buffer)
    {
        auto dataUnit = buffer.ReadNext();
        if (dataUnit)
        {
            m_priority = dataUnit->time;
            return true;
        }
        return false;
    }

    auto GetPriority(void) const { return m_priority; }

    bool ReadBuffer(BufferT& buffer)
    {
        auto dataUnit = buffer.ReadNext();
        if (dataUnit)
        {
            // Dump Time & Severity
            auto time     = dataUnit->getTime();
            auto severity = dataUnit->GetSeverity();

            m_dumper.dump(time, severity);

            // Dump Data
            static constexpr std::size_t bufferLen{ 1024 };
            char                         readBuffer[bufferLen];
            while (not dataUnit->Empty())
            {
                auto readLen = dataUnit->Read(readBuffer, bufferLen);
                if (readLen < 0 || readLen > bufferLen)
                {
                    std::cerr << __func__
                              << ":: Error, Invalid ReadLen:" << readLen
                              << ", bufferLen:" << bufferLen << std::endl;
                    break;
                }
                m_dumper.dump(readBuffer, readLen);
            }

            // mark read finish
            buffer.ReadFinish();
            return true;
        }
        return false;
    }

private:
    DumperT& m_dumper;
    uint64_t m_priority;
};

class BasicDumper
{
public:
    template <typename SeverityT>
    void dump(const timespec& time, SeverityT severity)
    {
        std::cout << std::put_time(std::localtime(&(time.tv_sec)), "%T") << ":"
                  << time.tv_nsec << " [" << severity.stringify() << "] ";
    }

    void dump(const char* buffer, ssize_t len) { std::cout.write(buffer, len); }
};

} // namespace dumper
} // namespace clogger
