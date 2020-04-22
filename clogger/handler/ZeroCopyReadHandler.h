/* @doc
 * filename: ZeroCopyReadHandler.h
 * Description:
 * ZeroCopyReadHandler is a class to read data from a log buffee using the
 * buffer ptr directly of dumper and indicate the dumper on success
 * interface required by dumper
 *          - getBuffStart();
 *          - getBuffMaxLen();
 *          - dump(dumpBuffPtr, TotWriteByte);
 */

#pragma once

#include <cstdio>
#include <ctime>
#include <iostream>

#include <scope_guard.hpp>

namespace clogger {
namespace handler {

template <typename LoggerType, typename DumperType>
class ZeroCopyReadHandler
{
public:
    using DumperT       = DumperType;
    using LoggerT       = LoggerType;
    using TimeTypeT     = timespec;
    using SeverityT     = typename LoggerT::SeverityT;
    using LoggerBufferT = typename LoggerT::LoggerBufferT;

public:
    explicit ZeroCopyReadHandler(DumperT& dumper)
      : m_dumper(dumper)
    {
    }

    bool handle(LoggerBufferT& buffer);

private:
    DumperT& m_dumper;
};

template <typename LT, typename DT>
bool ZeroCopyReadHandler<LT, DT>::handle(LoggerBufferT& buffer)
{
    auto logError =
      [](ssize_t writeByte, size_t TotWriteByte, size_t maxLen) -> void {
        std::cerr << __func__
                  << ":: Error: Invalid writeByte value:" << writeByte
                  << ", TotWriteByte: " << TotWriteByte
                  << ", max buffer len:" << maxLen << std::endl;
    };

    // get dataUnit from buffer
    auto dataUnit = buffer.ReadNext();
    bool success  = true;
    if (dataUnit)
    {
        size_t       TotWriteByte{ 0 };
        char*        dumpBuffPtr = m_dumper.getBuffStart();
        const size_t dumpBuffLen = m_dumper.getBuffMaxLen();

        // scope gaurd to move to the next
        auto localGuard = sg::make_scope_guard([&]() {
            // call read finish
            buffer.ReadFinish();

            // indicate dumpper to dump the buff and len
            success = m_dumper.dump(dumpBuffPtr, TotWriteByte);
        });

        // write time and severity into the bufferPtr
        auto time     = dataUnit->GetTime();
        auto severity = dataUnit->GetSeverity();

        // write time upto seconds
        ssize_t writeByte = std::strftime(
          dumpBuffPtr, dumpBuffLen, "%T", std::localtime(&(time.tv_sec)));
        if (writeByte <= 0 || (TotWriteByte += writeByte) > dumpBuffLen)
        {
            logError(writeByte, TotWriteByte, dumpBuffLen);
            return false;
        }

        // write time upto nano seconds
        writeByte = std::snprintf(dumpBuffPtr + TotWriteByte,
                                  dumpBuffLen - TotWriteByte,
                                  ".%09ld",
                                  time.tv_nsec);
        if (writeByte <= 0 || (TotWriteByte += writeByte) > dumpBuffLen)
        {
            logError(writeByte, TotWriteByte, dumpBuffLen);
            return false;
        }

        // write severity
        writeByte = std::snprintf(dumpBuffPtr + TotWriteByte,
                                  dumpBuffLen - TotWriteByte,
                                  " [%s] ",
                                  severity.stringify().c_str());
        if (writeByte <= 0 || (TotWriteByte += writeByte) > dumpBuffLen)
        {
            logError(writeByte, TotWriteByte, dumpBuffLen);
            return false;
        }

        // write log data
        while (not dataUnit->Empty())
        {
            writeByte = dataUnit->Read(dumpBuffPtr + TotWriteByte,
                                       dumpBuffLen - TotWriteByte);
            if (writeByte <= 0 || (TotWriteByte += writeByte) > dumpBuffLen)
            {
                logError(writeByte, TotWriteByte, dumpBuffLen);
                return false;
            }
        }
    }
    return success;
}

} // namespace handler
} // namespace clogger
