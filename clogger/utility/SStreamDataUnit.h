#pragma once

#include <chrono>
#include <ctime>
#include <sstream>

namespace clogger {
namespace utility {

template <typename SeverityType>
class SStreamDataUnit
{
public:
    using ThisT     = SStreamDataUnit<SeverityType>;
    using PriorityT = uint64_t;
    using TimeTypeT = timespec;
    using DataUnitT = std::stringstream;
    using SeverityT = SeverityType;

    void init(SeverityT _severity)
    {
        auto currTimePoint = std::chrono::high_resolution_clock::now();
        auto currTimePointNS =
          std::chrono::time_point_cast<std::chrono::nanoseconds>(currTimePoint);
        auto epocTimeNS = std::chrono::duration_cast<std::chrono::nanoseconds>(
          currTimePointNS.time_since_epoch());

        // Populating priority as nanoseconds count
        priority = epocTimeNS.count();

        // Populating time as timespec
        auto epocTimeSec =
          std::chrono::duration_cast<std::chrono::seconds>(epocTimeNS);

        epocTimeNS -= epocTimeSec;
        time = timespec{ epocTimeSec.count(), epocTimeNS.count() };

        // Populating severity
        severity = _severity;

        // clearing stringstream buffer
        std::stringstream().swap(data);
    }

    template <typename T>
    ThisT& operator<<(T val)
    {
        data << val;
        return *this;
    }

    ssize_t Read(void* addr, size_t len)
    {
        return data.read(static_cast<char*>(addr), len).gcount();
    }

    bool Empty() { return data.peek() == EOF; }

    auto& getTime() const { return time; }
    auto& GetSeverity() const { return severity; }

private:
    PriorityT priority{ 0 };
    TimeTypeT time;
    DataUnitT data;
    SeverityT severity;
};

} // namespace utility
} // namespace clogger
