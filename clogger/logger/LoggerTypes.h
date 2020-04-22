/* @doc
 * filename:    LoggerTypes.h
 * author:      ugupta
 * Description:
 * LoggerTypes class have aliases for various classes
 * that will be used for logger mechanism, if other types
 * need to be used for logger alias we can override the
 * aliases in the inherited classes
 */

#pragma once

#include "Logger.h"
#include "Severity.h"
#include "buffers/LoggerFRBuffer.h"

namespace clogger {
namespace logger {

template <typename DerivedT>
struct LoggerTypes
{
    using SeverityT     = logger::Severity;
    using DataUnitT     = logger::LoggerFRDataUnit<DerivedT>;
    using LoggerBufferT = logger::LoggerFRBuffer<DerivedT>;
    using LoggerT       = logger::Logger<DerivedT>;
};

struct DefaultLoggerTypes : public LoggerTypes<DefaultLoggerTypes>
{
};

} // namespace logger
} // namespace clogger
