/* @doc
 * filenaeme:   CloggerType.h
 * author:      ugupta
 * Description
 * Default CloggerType Struct to have default loggerType,
 * DumperType and HandlerType Info
 */

#pragma once

#include "dumper/DumperTypes.h"
#include "handler/HandlerTypes.h"
#include "logger/LoggerTypes.h"

namespace clogger {

template <typename LoggerTypes = logger::DefaultLoggerTypes,
          typename DumperTypes = dumper::DefaultDumperTypes,
          typename HandlerTypes =
            handler::DefaultHandlerTypes<LoggerTypes, DumperTypes>>
struct CLoggerTypes
  : public LoggerTypes
  , public DumperTypes
  , public HandlerTypes
{
};

using DefaultCloggerTypes = CLoggerTypes<>;

} // namespace clogger
