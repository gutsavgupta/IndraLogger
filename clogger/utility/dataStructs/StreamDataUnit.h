/* @doc
 * filename: StreamDataUnit.h
 * author: ugupta
 * date: 30th March 2020
 * Description:
 * StreamDataUnit, these data units coupled with buffer types can
 * be used to read and write (kind of format) from this
 */

#pragma once

#include "FastStream.h"
#include <chrono>
#include <ctime>
#include <sstream>

namespace clogger {
namespace utility {

template <typename SeverityType, typename StreamType>
class StreamDataUnit
{
public:
    using SeverityT = SeverityType;
    using StreamT   = StreamType;
    using TimeTypeT = timespec;
    using PriorityT = uint64_t;

public:
    template <typename T>
    StreamDataUnit& operator<<(T val);

    // Basic Data handling interfaces
    void    init(SeverityT _severity);
    ssize_t Read(char* addr, size_t len);
    ssize_t Write(const char* addr, size_t len);

    // Basic State interfaces
    bool  Empty() { return data.eof(); }
    auto& GetTime() const { return time; }
    auto& GetSeverity() const { return severity; }
    auto& GetPriority() const { return priority; }

    // Reset Data unit
    void ResetStream();

private:
    PriorityT  priority{ 0 };
    TimeTypeT  time{ 0, 0 };
    SeverityT  severity;
    StreamType data;
};

template <typename Enum, typename Stream>
void StreamDataUnit<Enum, Stream>::init(SeverityT _severity)
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

    // reset the stream
    ResetStream();
}

template <typename Enum, typename Stream>
template <typename T>
inline auto StreamDataUnit<Enum, Stream>::operator<<(T val)
  -> StreamDataUnit<Enum, Stream>&
{
    data << val;
    return *this;
}

template <typename Enum, typename Stream>
inline ssize_t StreamDataUnit<Enum, Stream>::Read(char* addr, size_t len)
{
    return data.read(addr, len).gcount();
}

template <typename Enum, typename Stream>
inline ssize_t StreamDataUnit<Enum, Stream>::Write(const char* addr, size_t len)
{
    auto endPos = data.tellp();
    return data.write(addr, len).tellp() - endPos;
}

template <typename Enum, typename Stream>
inline void StreamDataUnit<Enum, Stream>::ResetStream()
{
    data.reset();
}

} // namespace utility
} // namespace clogger
