#pragma once

namespace clogger {
namespace logger {

class LogBuffer
{
public:
    LogBuffer() = default;

    // temp interface by LoggerBase
    LogBuffer(size_t bufferSize);
    bool  clear();
    DataT next();

protected:
};

} // namespace logger
} // namespace clogger
