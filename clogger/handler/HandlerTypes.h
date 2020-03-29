/* @doc
 * filename:    HandlerTypes.h
 * author:      ugupta
 * Description:
 * HandlerTypes contain default handler for
 * ReadHandler and priorityHandler type
 */

#pragma once

#include <handler/PriorityHandler.h>
#include <handler/ZeroCopyReadHandler.h>

namespace clogger {
namespace handler {

template <typename LoggerTypes, typename DumperTypes>
struct DefaultHandlerTypes
{
    using ReadHandlerT     = ZeroCopyReadHandler<typename LoggerTypes::LoggerT,
                                             typename DumperTypes::DumperT>;
    using PriorityHandlerT = PriorityHandler<typename LoggerTypes::LoggerT>;
};

} // namespace handler
} // namespace clogger
