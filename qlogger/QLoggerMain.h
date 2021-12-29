/* @doc
 * filename:    QLoggerMain.h
 * author:      ugupta
 * description:
 * QLoggerMain Singleton Class defines following main functionality for the
 * logger subsystem
 * 1. Map of loggers
 * 2. Single dumper
 * 3. Dump functionality
 *      - Based on steps
 *      - Based on time
 * 4. Configration interface for configurator class (TODO)
 */

#pragma once

#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>

namespace qlogger {

template <typename QLoggerTypes>
class QLoggerMain
{
public:
    using QLoggerMainT = QLoggerMain<QLoggerTypes>;
    using LoggerT      = typename QLoggerTypes::LoggerT;
    using DumperT      = typename QLoggerTypes::DumperT;
    using SeverityT    = typename QLoggerTypes::SeverityT;
    using IndexT       = uint64_t;

public:
    // Getter interface
    static QLoggerMainT& GetInstance();

    LoggerT& GetLogger();

    LoggerT& GetLogger(IndexT LoggerId);

    DumperT& GetDumper();

    // Functionality interface
    bool Run(bool tillComplete = false);

    bool ConfigureSeverity(SeverityT severity, bool configureRest = true);

    bool ConfigureBufferSize(size_t bufferSize, bool configureRest = true);

protected:
    QLoggerMain()
      : m_bufferSize(1ULL << 15)
      , m_severity(SeverityT::DEBUG)
    {
        m_loggerMap.reserve(64);
    }

    QLoggerMain(QLoggerMain&)  = delete;
    QLoggerMain(QLoggerMain&&) = delete;

    IndexT GetCurrThreadId() const;

protected:
    using LoggerPtrT = std::unique_ptr<LoggerT>;

    // QLogger main object ptr
    static std::unique_ptr<QLoggerMainT> s_qloggerPtr;

    // Mutex instances for thread safety
    static std::mutex s_instanceMutex;
    static std::mutex s_loggerMapMutex;
    static std::mutex s_severityMutex;
    static std::mutex s_bufferSizeMutex;

    // Data members
    std::unordered_map<IndexT, LoggerPtrT> m_loggerMap;

    size_t    m_bufferSize;
    SeverityT m_severity;
    DumperT   m_dumper;
};

template <typename T>
std::unique_ptr<QLoggerMain<T>> QLoggerMain<T>::s_qloggerPtr;

template <typename T>
std::mutex QLoggerMain<T>::s_instanceMutex;

template <typename T>
std::mutex QLoggerMain<T>::s_loggerMapMutex;

template <typename T>
std::mutex QLoggerMain<T>::s_severityMutex;

template <typename T>
std::mutex QLoggerMain<T>::s_bufferSizeMutex;

template <typename T>
auto QLoggerMain<T>::GetInstance() -> QLoggerMainT&
{
    // TODO: should we use branch predictor optimization
    if (s_qloggerPtr == nullptr)
    {
        // Making this thread safe, as it can be possible that
        // singleton object can be called via multiple thread
        const std::lock_guard<std::mutex> lock(s_instanceMutex);
        if (s_qloggerPtr == nullptr)
        {
            s_qloggerPtr.reset(new QLoggerMainT());
        }
    }
    return *s_qloggerPtr;
}

template <typename T>
auto QLoggerMain<T>::GetCurrThreadId() const -> IndexT
{
    auto hasher = std::hash<std::thread::id>();
    return hasher(std::this_thread::get_id());
}

template <typename T>
auto QLoggerMain<T>::GetLogger() -> LoggerT&
{
    // This call return a logger for current thread
    // creates one if current thread doesn't own a logger
    return GetLogger(GetCurrThreadId());
}

template <typename T>
auto QLoggerMain<T>::GetLogger(IndexT loggerId) -> LoggerT&
{
    auto loggerItr = m_loggerMap.find(loggerId);
    if (loggerItr == m_loggerMap.end())
    {
        // construct a new logger with logger
        // with m_severity and m_buffersize, this
        // need to be thread safe
        std::lock_guard<std::mutex> lock(s_loggerMapMutex);
        loggerItr =
          m_loggerMap
            .emplace(loggerId,
                     std::make_unique<LoggerT>(m_severity, m_bufferSize))
            .first;
    }
    return *(loggerItr->second);
}

template <typename T>
auto QLoggerMain<T>::GetDumper() -> DumperT&
{
    return m_dumper;
}

template <typename T>
auto QLoggerMain<T>::Run(bool tillComplete) -> bool
{
    // we iterate through each stored logger to calculate the
    // lowest ranl/priority (lower the priority value, higher the priority)
    // We assume, since number of logger might not be large (max 4~5), so
    // iterating each time should not cause harm
    // TODO: we can implement dispatch class to take this decision for us
    // Define Read and Priority handler
    using PriorityHandlerT = typename T::PriorityHandlerT;
    using ReadHandlerT     = typename T::ReadHandlerT;

    auto priorityHandler = PriorityHandlerT();
    auto readHandler     = ReadHandlerT(m_dumper);
    while (1)
    {
        auto     minLoggerItr{ m_loggerMap.end() };
        uint64_t minPriority{ std::numeric_limits<uint64_t>::max() };

        for (auto loggerItr = m_loggerMap.begin();
             loggerItr != m_loggerMap.end();
             ++loggerItr)
        {
            if (not(loggerItr->second)->HandleBuffer(priorityHandler))
            {
                priorityHandler.reset();
                continue;
            }

            if (priorityHandler.value() < minPriority)
            {
                minPriority  = priorityHandler.value();
                minLoggerItr = loggerItr;
            }
        }

        // read the logger using the ReadHandler
        if (minLoggerItr != m_loggerMap.end())
        {
            if (not(minLoggerItr->second)->HandleBuffer(readHandler))
            {
                std::cerr << __func__
                          << ":: Error while reading buffer data, stoping the "
                             "run process"
                          << std::endl;
                return false;
            }
        }
        else if (tillComplete)
        {
            break;
        }
    }
    return true;
}

template <typename T>
bool QLoggerMain<T>::ConfigureSeverity(SeverityT severity, bool configureRest)
{
    if (m_severity != severity)
    {
        std::lock_guard<std::mutex> lock(s_severityMutex);

        // assign the new severity
        m_severity = severity;

        if (not configureRest)
        {
            return true;
        }

        // reset the reverity of each logger
        for (auto& loggerPair : m_loggerMap)
        {
            loggerPair.second.SetSeverity(m_severity);
        }
    }
    return true;
}

template <typename T>
bool QLoggerMain<T>::ConfigureBufferSize(size_t bufferSize, bool configureRest)
{
    if (m_bufferSize != bufferSize)
    {
        std::lock_guard<std::mutex> lock(s_bufferSizeMutex);

        // assign the new bufferSize
        m_bufferSize = bufferSize;

        if (not configureRest)
        {
            return true;
        }

        // reset the reverity of each logger
        for (auto& loggerPair : m_loggerMap)
        {
            loggerPair.second.SetBufferSize(m_bufferSize);
        }
    }
    return true;
}

} // namespace qlogger
