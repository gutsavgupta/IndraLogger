/*
 * Main Logger Object and Interaface required by CLoggerMain class
 */

#ifndef CLOGGER_H
#define CLOGGER_H

template<typename CloggerDataType, typename BufferType>
class Clogger
{
public:
    using LOGGER_ID   = uint64_t;
    using LOGGER_DATA = CloggerDataType;

public:

    // time priority detection
    // TODO: get time of last read log

    // read a single log buffer from logger
    // return the read char counts
    size_t ReadBuffer(void* buffer, size_t bufferLen);

    // Function to read log, need to deine '<<' operator
    // overloads for this logger type, delieniate to 
    // CloggerDataType
    template <typename T>
    Clogger& operator<<(T var);

protected:
    
};

#endif
