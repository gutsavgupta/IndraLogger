/* @doc
 * filenaeme:   QLoggerType.h
 * author:      ugupta
 * Description
 * Default QLoggerType Struct to have default loggerType,
 * DumperType and HandlerType Info
 */

#pragma once

#include "dumper/DumperTypes.h"
#include "handler/HandlerTypes.h"
#include "logger/LoggerTypes.h"

namespace qlogger {

template <typename LoggerTypes = logger::DefaultLoggerTypes,
          typename DumperTypes = dumper::DefaultDumperTypes,
          typename HandlerTypes =
            handler::DefaultHandlerTypes<LoggerTypes, DumperTypes>>
struct QLoggerTypes
  : public LoggerTypes
  , public DumperTypes
  , public HandlerTypes
{
};

using DefaultQLoggerTypes = QLoggerTypes<>;

} // namespace qlogger
