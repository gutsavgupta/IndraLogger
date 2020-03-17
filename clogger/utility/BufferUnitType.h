#pragma once

#include <chrono>
#include <sstream>

namespace clogger {
namespace utility {

template <typename SeverityType>
class BufferUnitType
{
public:
    using ThisT     = BufferUnitType<SeverityType>;
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
        data.str("");
    }

    template <typename T>
    BufferUnitType& operator<<(T val)
    {
        data << val;
        return *this;
    }

private:
    TimeTypeT time;
    DataUnitT data;
    SeverityT severity;
};

} // namespace utility
} // namespace clogger
