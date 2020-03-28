#pragma once

#include <chrono>
#include <sstream>

namespace clogger {
namespace utility {

template <typename SeverityType>
class SStreamDataUnit
{
public:
    using ThisT     = SStreamDataUnit<SeverityType>;
    using TimeTypeT = uint64_t;
    using DataUnitT = std::stringstream;
    using SeverityT = SeverityType;

    void init(SeverityT _severity)
    {
        auto currTimePoint = std::chrono::high_resolution_clock::now();
        auto currTimePointNS =
          std::chrono::time_point_cast<std::chrono::nanoseconds>(currTimePoint);
        auto epocTimeNS = std::chrono::duration_cast<std::chrono::nanoseconds>(
          currTimePointNS.time_since_epoch());
        time     = epocTimeNS.count();
        severity = _severity;
        data.swap(std::stringstream());
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

    bool Empty() { return data.peek() != EOF; }

private:
    TimeTypeT time;
    DataUnitT data;
    SeverityT severity;
};

} // namespace utility
} // namespace clogger
