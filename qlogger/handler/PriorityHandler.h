/* @doc
 * filename: PriorityHandler.h
 * Description:
 * PriorityHandler is a basic class to read prioriy from a logger class
 */

#pragma once

#include <cstdint>
#include <limits>

namespace qlogger {
namespace handler {

template <typename LoggerType>
class PriorityHandler
{
public:
    using LoggerT       = LoggerType;
    using LoggerBufferT = typename LoggerT::LoggerBufferT;
    using DataUnitT     = typename LoggerBufferT::DataUnitT;
    using PriorityT     = typename DataUnitT::PriorityT;

public:
    bool handle(LoggerBufferT& buffer);

    auto value() const { return m_priority; }

    void reset() { m_priority = std::numeric_limits<uint64_t>::max(); }

private:
    uint64_t m_priority{ std::numeric_limits<uint64_t>::max() };
};

template <typename T>
bool PriorityHandler<T>::handle(LoggerBufferT& buffer)
{
    auto dataUnit = buffer.ReadNext();
    if (dataUnit)
    {
        m_priority = dataUnit->GetPriority();
        return true;
    }
    return false;
}

} // namespace handler
} // namespace qlogger
