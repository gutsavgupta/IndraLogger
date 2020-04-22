#pragma once

#include "LoggerBufferBase.h"
#include <sstream>
#include <utility/dataStructs/FastBuffer.h>
#include <utility/dataStructs/FastStream.h>
#include <utility/dataStructs/FixedRingBuffer.h>
#include <utility/dataStructs/StreamDataUnit.h>
#include <utility/dataStructs/StringBuffer.h>

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

namespace {

using LoggerFRBufferT = utility::FastBuffer<utility::StringBuffer>;
using LoggerFRStreamT = utility::FastStream<LoggerFRBufferT>;

} // local namespace

template <typename LoggerTypes, typename StreamType = LoggerFRStreamT>
struct LoggerFRDataUnit
  : public utility::StreamDataUnit<typename LoggerTypes::SeverityT, StreamType>
{
public:
    using SeverityT = typename LoggerTypes::SeverityT;
    using BaseT     = utility::StreamDataUnit<SeverityT, StreamType>;
    using BaseT::BaseT;
};

} // namespace logger
} // namespace clogger
