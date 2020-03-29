#pragma once

#include <logger/buffers/LoggerBufferBase.h>
#include <utility/dataStructs/FixedRingBuffer.h>
#include <utility/dataStructs/StreamDataUnit.h>

namespace clogger {
namespace logger {

template <typename LoggerTypes>
class LoggerFRBuffer
  : public utility::FixedRingBuffer<typename LoggerTypes::DataUnitT>
  , public LoggerBufferBase<LoggerFRBuffer<LoggerTypes>, LoggerTypes>
{
public:
    using SeverityT = typename LoggerTypes::SeverityT;
    using DataUnitT = typename LoggerTypes::DataUnitT;
    using FRBufferT = utility::FixedRingBuffer<DataUnitT>;

    // inheriting fixed ring buffer construtor
    using FRBufferT::FRBufferT;
};

template <typename LoggerTypes>
struct LoggerFRDataUnit
  : public utility::StreamDataUnit<typename LoggerTypes::SeverityT>
{
};

} // namespace logger
} // namespace clogger
