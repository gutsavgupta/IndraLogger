/* @doc
 * filename:    Logger.h
 * author:      ugupta
 * Description:
 * Logger class is the main class to write log to and read
 * logs from. We will be using objects of this class (templated
 * on logger types, from which we get info of bufferType and
 * Severity type). LoggerMain class will interact with Logger's
 * interface to configure/read the logs
 */

#pragma once

#include <iostream>

namespace clogger {
namespace logger {

template <typename LoggerTypes>
class Logger
{
public:
    using LoggerBufferT = typename LoggerTypes::LoggerBufferT;
    using SeverityT     = typename LoggerTypes::SeverityT;

public:
    Logger()
      : Logger(SeverityT::INFO)
    {
    }
    Logger(SeverityT severity)
      : m_severity(severity)
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

    // handler interfaces
    template <typename HandlerT>
    bool HandleBuffer(HandlerT& handler);

    // Write interfaces
    auto WriteNext(SeverityT severity) { return m_buffer.WriteNext(severity); }
    auto WriteFinish() { return m_buffer.WriteFinish(); }

    // Setter interfaces
    auto SetBufferSize(size_t bufferSize);
    auto SetSeverity(SeverityT severity) { m_severity = severity; }

    // State interfaces
    auto ClearBuffer() { return m_buffer.clear(); }
    auto GetSeverity() const { return m_severity; }
    bool CheckSeverity(const SeverityT severity) const;

protected:
    LoggerBufferT m_buffer;
    SeverityT     m_severity{ SeverityT::ALERTS };
};

template <typename T>
template <typename H>
inline bool Logger<T>::HandleBuffer(H& handler)
{
    return handler.handle(m_buffer);
}

template <typename T>
inline bool Logger<T>::CheckSeverity(const SeverityT severity) const
{
    return severity <= m_severity;
}

template <typename T>
inline auto Logger<T>::SetBufferSize(size_t bufferSize)
{
    return m_buffer.SetSize(bufferSize);
}

} // namespace logger
} // namespace clogger

