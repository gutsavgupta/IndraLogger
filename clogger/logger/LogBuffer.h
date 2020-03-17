/* @doc
 * TODO
 */

#pragma once

#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>

namespace clogger {
namespace logger {

template <typename SeverityType, typename BufferType>
class LogBuffer
{
public:
    using SeverityT = SeverityType;
    using BufferT   = BufferType;
    using DataUnitT = typename BufferT::DataUnitT;

public:
    LogBuffer() = default;
    LogBuffer(size_t bufferSize)
      : m_buffer(bufferSize)
    {
    }

    bool SetSize(size_t size) { return m_buffer.SetSize(size); }

    void clear() { m_buffer.clear(); }

    bool empty() { return m_buffer.empty(); }

    bool filled() { return m_buffer.filled(); }

    DataUnitT* WriteNext(const SeverityT severity)
    {
        try
        {
            // Current behaviour is to drop the
            // upcoming logs instead of dropping the
            // registered logs
            if (filled())
            {
                std::cerr << __func__ << ":: Log drops for severity:"
                          << severity.stringify() << std::endl;
                return nullptr;
            }
            if (m_writeState == State::BLOCK)
            {
                std::cerr << __func__
                          << ":: overriting the current log buffer, ideally "
                             "call WriteFinish() after the logging is "
                             "completed to next buffer"
                          << std::endl;
            }

            auto bufferPtr = m_buffer.getHead();

            bufferPtr->init();

            // make the write state as BLOCK
            m_writeState = State::BLOCK;

            return bufferPtr;
        }
        catch (const std::exception& e)
        {
            std::cerr << __func__ << ":: execption occured, reason:" << e.what()
                      << std::endl;
            return nullptr;
        }
    }

    void WriteFinish()
    {
        if (m_writeState == State::BLOCK && not filled())
        {
            // need to increment the head to next
            // this will allow reader to read the data
            m_buffer.incrHead();
        }
        else
        {
            std::cerr << __func__
                      << ":: finish is called for READY buffer state"
                      << std::endl;
        }
        m_writeState = State::READY;
    }

    DataUnitT* ReadNext()
    {
        try
        {
            if (empty())
            {
                return nullptr;
            }
            if (m_readState == State::BLOCK)
            {
                std::cerr << __func__
                          << ":: Reading back the same log, we should call "
                             "ReadFinish() after the reading of log is done"
                          << std::endl;
            }

            // make the read state as blocked
            m_readState = State::BLOCK;

            return m_buffer.getTail();
        }
        catch (const std::exception& e)
        {
            std::cerr << __func__ << ":: execption occured, reason:" << e.what()
                      << std::endl;
            return nullptr;
        }
    }

    void ReadFinish()
    {
        if (m_readState == State::BLOCK && not empty())
        {
            m_buffer.incrTail();
        }
        else
        {
            std::cerr << __func__
                      << ":: finish is called for READY buffer state"
                      << std::endl;
        }
        m_readState = State::READY;
    }

protected:
    enum class State
    {
        READY,
        BLOCK
    };

    BufferT m_buffer;
    State   m_writeState{ State::READY };
    State   m_readState{ State::READY };
};

} // namespace logger
} // namespace clogger
