/* @doc
 * LoggerBufferBase.h
 * description: Define basic functions that should be defined in any
 * loggerBuffer class, This base class is only for inheritance, hence
 * we are making it's constructor as prrotected
 */

#pragma once

#include <iostream>
#include <utility/macroDefs/CheckMemFunc.h>

namespace clogger {
namespace logger {

template <typename DerivedT, typename LoggerTypes>
class LoggerBufferBase
{
public:
    // DerivedT type should contain some type alias
    using DataUnitT = typename LoggerTypes::DataUnitT;
    using SeverityT = typename LoggerTypes::SeverityT;

private:
    // DerivedT should define above functions
    CHECK_MEMBER_FUNC_EXIST(DerivedT, empty, bool(void));
    CHECK_MEMBER_FUNC_EXIST(DerivedT, filled, bool(void));
    CHECK_MEMBER_FUNC_EXIST(DerivedT, getHead, DataUnitT*(void));
    CHECK_MEMBER_FUNC_EXIST(DerivedT, getTail, DataUnitT*(void));
    CHECK_MEMBER_FUNC_EXIST(DerivedT, incrHead, void(void));
    CHECK_MEMBER_FUNC_EXIST(DerivedT, incrTail, void(void));

protected:
    LoggerBufferBase() = default;

    DerivedT*       GetDerived() { return static_cast<DerivedT*>(this); }
    const DerivedT* GetDerived() const
    {
        return static_cast<const DerivedT*>(this);
    }

public:
    DataUnitT* WriteNext(SeverityT severity);
    DataUnitT* ReadNext();
    void       WriteFinish();
    void       ReadFinish();

protected:
    enum class State
    {
        READY,
        BLOCK
    };

    State m_writeState{ State::READY };
    State m_readState{ State::READY };
};

template <typename DerivedT, typename LoggerTypes>
auto LoggerBufferBase<DerivedT, LoggerTypes>::WriteNext(
  const SeverityT severity) -> DataUnitT*
{
    try
    {
        // Current behaviour is to drop the
        // upcoming logs instead of dropping the
        // registered logs
        if (GetDerived()->filled())
        {
            std::cerr << __func__
                      << ":: Log drops for severity:" << severity.stringify()
                      << std::endl;
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

        auto bufferPtr = GetDerived()->getHead();

        bufferPtr->init(severity);

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

template <typename DerivedT, typename LoggerTypes>
auto LoggerBufferBase<DerivedT, LoggerTypes>::WriteFinish() -> void
{
    if (m_writeState == State::BLOCK && not GetDerived()->filled())
    {
        // need to increment the head to next
        // this will allow reader to read the data
        GetDerived()->incrHead();
    }
    else
    {
        std::cerr << __func__ << ":: finish is called for READY buffer state"
                  << std::endl;
    }
    m_writeState = State::READY;
}

template <typename DerivedT, typename LoggerTypes>
auto LoggerBufferBase<DerivedT, LoggerTypes>::ReadNext() -> DataUnitT*
{
    try
    {
        if (GetDerived()->empty())
        {
            return nullptr;
        }

        // make the read state as blocked
        m_readState = State::BLOCK;

        return GetDerived()->getTail();
    }
    catch (const std::exception& e)
    {
        std::cerr << __func__ << ":: execption occured, reason:" << e.what()
                  << std::endl;
        return nullptr;
    }
}

template <typename DerivedT, typename LoggerTypes>
auto LoggerBufferBase<DerivedT, LoggerTypes>::ReadFinish() -> void
{
    if (m_readState == State::BLOCK && not GetDerived()->empty())
    {
        GetDerived()->incrTail();
    }
    else
    {
        std::cerr << __func__ << ":: finish is called for READY buffer state"
                  << std::endl;
    }
    m_readState = State::READY;
}

} // namespace logger
} // namespace clogger
