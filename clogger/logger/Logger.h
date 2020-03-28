/* @doc
 * LoggerClass
 * This class should standardize the interface required
 * by LoggerMain class and interface provide to user
 * Also since this class will be exposing functionality
 * in fast paths of code, we recommend avoid adding virtual
 * interfaces in the base class
 *
 * Main interfaces
 *  - TODO
 *
 * Limitation
 *  - TODO
 */

#pragma once

#include <iostream>
#include <utility/Severity.h>

namespace clogger {
namespace logger {

template <typename BufferT, typename SeverityT = typename utility::Severity>
class Logger
{
public:
    Logger()
      : Logger(SeverityT::INFO, BufferT::DEFAULT_BUFFER_SIZE)
    {
    }
    Logger(SeverityT severity)
      : Logger(severity, BufferT::DEFAULT_BUFFER_SIZE)
    {
    }
    Logger(size_t bufferSize)
      : Logger(SeverityT::INFO, bufferSize)
    {
    }
    Logger(SeverityT severity, size_t bufferSize)
      : m_severity(severity)
      , m_buffer(bufferSize)
    {
    }

    void SetSeverity(SeverityT severity) { m_severity = severity; }
    bool SetBufferSize(size_t bufferSize = BufferT::DEFAULT_BUFFER_SIZE)
    {
        return m_buffer.SetSize(bufferSize);
    }

    template <typename ReaderT>
    bool ReadPriority(ReaderT& reader)
    {
        return reader.readPriority(&m_buffer);
    }

    template <typename ReaderT>
    bool ReadBuffer(ReaderT& reader)
    {
        return reader.readBuffer(&m_buffer);
    }

    bool CheckSeverity(const SeverityT severity) const
    {
        return severity <= m_severity;
    }

    typename BufferT::BufferUnitT* WriteBuffer()
    {
        return m_buffer.WriteNext();
    }

    void WriteFinish() { m_buffer.WriteFinish(); }
    auto GetSeverity() const { return m_severity; }
    auto ClearBuffer() { return m_buffer.clear(); }

protected:
    BufferT   m_buffer;
    SeverityT m_severity{ SeverityT::ALERTS };
};

} // namespace logger
} // namespace clogger

