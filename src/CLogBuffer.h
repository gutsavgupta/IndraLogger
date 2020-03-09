
#ifndef CLOGBUFFER_H
#define CLOGBUFFER_H

class CLogBuffer
{
public:
    CLogBuffer();

    // Configure function
    bool Configure();
    bool SetSize(size_t size);

    // Get buffer to print log
    BufferType& GetBuffer();
    
    // Read Buffer from last read
    size_t ReadBuffer(void* buffer, size_t bufferLen);

    // '<<' operator overloading
    template <typename T>
    CLogBuffer& operator<<(T var);

protected:
    using PriorityType = uint64_t;
    using BufferType   = std::iostream;
    using UnitLogType  = std::pair<PriorityType, BufferType>;

    std::vector<UnitLogType> m_buffer;
    size_t m_TotalBufferCnt{1000};

    // Single read and write operation
    size_t m_bufferHead{0};
    size_t m_bufferTail{0};
};

#endif
