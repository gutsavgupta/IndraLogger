/*
 * Main Logger Object and Interaface required by CLoggerMain class
 */

#ifndef CLOGGER_H
#define CLOGGER_H

template<typename Derived, typename BufferType>
class Clogger
{
public:
    using LOGGER_ID   = uint64_t;
    using BUFFER_TPE  = BufferType;

public:
    Clogger();

    // BufferConfigure
    void Configure();

    // time priority detection
    bool ReadLastTime(BufferType::TimeType& timePoint);


    // read a single log buffer from logger
    // return the read char counts
    size_t ReadBuffer(void* buffer, size_t bufferLen);

    // Function to read log, need to deine '<<' operator
    // overloads for this logger type, delieniate to 
    // CloggerDataType
    template <typename T>
    Clogger& operator<<(T var);

protected:
    BUFFER_TYPE m_buffer;   
};

#endif
